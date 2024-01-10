#include "../include/my_conditional_variable.h"

MyCondVar::MyCondVar()
{
	cv_init(&my_cv);
}

MyCondVar::~MyCondVar()
{
	cv_destroy(&my_cv);
}

void MyCondVar::wait()
{
	cv_wait(&my_cv, predicate.native_handle());
}

void MyCondVar::signal()
{
	cv_signal(&my_cv);
}

void MyCondVar::broadcast()
{
    cv_broadcast(&my_cv);
}

void MyCondVar::enter_critical_section()
{
    #if defined(__linux) || defined(__MACH__)
		predicate.lock();
	#else
		EnterCriticalSection(&predicate);
	#endif //__linux
}

void MyCondVar::leave_critical_section()
{
    #if defined(__linux) || defined(__MACH__)
		predicate.unlock();
	#else
		LeaveCriticalSection(&predicate);
	#endif //__linux
}

my_predicate* MyCondVar::get_predicate_native_handle()
{
    #if defined(__linux) || defined(__MACH__)
		return predicate.native_handle();
	#else
		return &predicate;
	#endif //__linux
}

void MyCondVar::wait(MyMutex& mutex)
{
    cv_wait(&my_cv, mutex.native_handle());
}