#ifndef MY_THREAD_MY_MUTEX_H
#define MY_THREAD_MY_MUTEX_H

#include "../portable_types/portable_mutex.h"

class MyMutex
{
public:
	MyMutex() = default;
	~MyMutex();
    MyMutex& operator=(const MyMutex&) = delete;
    MyMutex(const MyMutex &) = default;
public:
	void lock();
	void unlock();
	my_mutex_t* native_handle();
private:
	my_mutex_t my_mutex = create_mutex();
};

#endif //MY_THREAD_MY_MUTEX_H
