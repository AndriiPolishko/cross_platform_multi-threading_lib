#ifndef MY_THREAD_MY_CONDITIONAL_VARIABLE_H
#define MY_THREAD_MY_CONDITIONAL_VARIABLE_H
#include "../portable_types/portable_cond_var.h"
#include "../include/my_mutex.h"
class MyCondVar
{
public:
	MyCondVar();
	~MyCondVar();
	MyCondVar(const MyCondVar &) = delete;
	MyCondVar operator=(const MyCondVar) = delete;
public:
	void wait(my_mutex_t* mutex);
	void signal();
private:
	my_cond my_cv;
};

#endif //MY_THREAD_MY_CONDITIONAL_VARIABLE_H
