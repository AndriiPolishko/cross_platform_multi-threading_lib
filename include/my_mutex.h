#ifndef MY_THREAD_MY_MUTEX_H
#define MY_THREAD_MY_MUTEX_H

#include "../portable_types/portable_mutex.h"

class MyMutex
{
private:
	my_mutex_t my_mutex = create_mutex();
public:
	MyMutex operator=(const MyMutex) = delete;
	MyMutex(const MyMutex &) = delete;
public:
	MyMutex() = default;
	void lock();
	void unlock();
	my_mutex_t* native_handle();
	~MyMutex();
};

#endif //MY_THREAD_MY_MUTEX_H
