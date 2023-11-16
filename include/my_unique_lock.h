#ifndef MY_THREAD_MY_UNIQUE_LOCK_H
#define MY_THREAD_MY_UNIQUE_LOCK_H

#include "my_mutex.h"

class MyUniqueLock
{
public:
    explicit MyUniqueLock(MyMutex& mutex);
    ~MyUniqueLock();

    MyUniqueLock(const MyUniqueLock&) = delete;
    MyUniqueLock& operator=(const MyUniqueLock&) = delete;

    MyUniqueLock(MyUniqueLock&& other) noexcept;

    void lock();
    void unlock();

private:
    MyMutex& mutex_;
    bool locked_;
};

#endif // MY_THREAD_MY_UNIQUE_LOCK_H
