#ifndef MY_THREAD_MY_CONDITIONAL_VARIABLE_H
#define MY_THREAD_MY_CONDITIONAL_VARIABLE_H
#include "../portable_types/portable_cond_var.h"
#include "../include/my_mutex.h"
class MyCondVar
{
private:
	my_cond my_cv;

public:
	MyCondVar();
	~MyCondVar();
	void wait(MyMutex mutex);
	void signal();
public:
	MyCondVar(const MyCondVar &) = delete;
	MyCondVar operator=(const MyCondVar) = delete;
};

#endif //MY_THREAD_MY_CONDITIONAL_VARIABLE_H
