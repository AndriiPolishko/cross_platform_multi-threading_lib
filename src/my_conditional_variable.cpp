#include "../include/my_conditional_variable.h"

MyCondVar::MyCondVar()
{
	cv_init(&my_cv);
}

MyCondVar::~MyCondVar()
{
	cv_destroy(&my_cv);
}

void MyCondVar::wait(my_mutex_t* mutex)
{
	cv_wait(&my_cv, mutex);
}

void MyCondVar::signal()
{
	cv_signal(&my_cv);
}