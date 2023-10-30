#ifndef TERM_PROJECT_MY_THREAD_H
#define TERM_PROJECT_MY_THREAD_H

#include "../portable_types/portable_thread.h"

class MyThread
{
	my_thread_t my_thread;

public:
	MyThread() = default;

	~MyThread();

	template <typename Callable, typename... Args>
	explicit MyThread(Callable&& func, Args&&... args);
	void join(retval val = nullptr) const;
};

template <typename Callable, typename... Args>
MyThread::MyThread(Callable&& func, Args&&... args)
{

	my_thread = thread_create(&my_thread, func, args...);
}


#endif //TERM_PROJECT_MY_THREAD_H
