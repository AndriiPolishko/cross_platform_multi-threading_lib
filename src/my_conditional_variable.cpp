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
	#ifdef __linux
		predicate.lock();
	#else
		EnterCriticalSection(&predicate);
	#endif //__linux
}

void MyCondVar::leave_critical_section()
{
	#ifdef __linux
		predicate.unlock();
	#else
		LeaveCriticalSection(&predicate);
	#endif //__linux
}

my_predicate* MyCondVar::get_predicate_native_handle()
{
	#ifdef __linux
		return predicate.native_handle();
	#else
		return &predicate;
	#endif //__linux
}