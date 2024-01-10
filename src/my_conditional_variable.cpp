#include "../include/my_conditional_variable.h"

MyCondVar::MyCondVar()
{
	cv_init(&my_cv);
}

MyCondVar::~MyCondVar()
{
	cv_destroy(&my_cv);
}

void MyCondVar::wait(MyMutex* mutex)
{
	cv_wait(&my_cv, mutex->native_handle());
}

void MyCondVar::signal()
{
	cv_signal(&my_cv);
}

void MyCondVar::broadcast()
{
    cv_broadcast(&my_cv);
}