#ifndef MY_THREAD_MY_LOCK_GUARD_H
#define MY_THREAD_MY_LOCK_GUARD_H

#include "my_mutex.h"

class MyLockGuard
{
public:
	MyLockGuard(MyMutex& mutex) : m_mutex(mutex) {
		m_mutex.lock();
	}

	~MyLockGuard()
	{
		m_mutex.unlock();
	}
	MyLockGuard(const MyLockGuard&) = delete;
	MyLockGuard operator=(MyLockGuard&) = delete;
private:
	MyMutex& m_mutex;
};

#endif //MY_THREAD_MY_LOCK_GUARD_H
