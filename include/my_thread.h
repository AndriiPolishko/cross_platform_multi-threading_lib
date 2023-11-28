#ifndef TERM_PROJECT_MY_THREAD_H
#define TERM_PROJECT_MY_THREAD_H

#include "../portable_types/portable_thread.h"

class MyThread
{
public:
	MyThread() = default;
	template <typename Callable, typename... Args>
	MyThread(Callable&& func, Args&&... args)
	{
		my_thread = thread_create(&my_thread, func, args...);
	}
	~MyThread();
public:
	void join(retval val = nullptr) const;
	template <typename Callable, typename... Args>
	void my_thread_create(Callable&& func, Args&&... args);
	my_thread_t native_handle() { return my_thread; }
private:
	my_thread_t my_thread;
};

template <typename Callable, typename... Args>
void MyThread::my_thread_create(Callable&& func, Args&&... args)
{
	my_thread = thread_create(&my_thread, func, args...);
}

#endif //TERM_PROJECT_MY_THREAD_H
