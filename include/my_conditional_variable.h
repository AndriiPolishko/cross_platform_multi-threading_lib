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
	void wait();
    void wait(MyMutex &mutex);
	void signal();
    void broadcast();
	void enter_critical_section();
	void leave_critical_section();

	#ifdef __linux
		my_mutex_t* get_predicate_native_handle();
	#else
		my_predicate* get_predicate_native_handle();
	#endif
private:
	my_cond my_cv;
	#ifdef __linux
		MyMutex predicate;
	#else
		my_predicate predicate;
	#endif
};

#endif //MY_THREAD_MY_CONDITIONAL_VARIABLE_H
