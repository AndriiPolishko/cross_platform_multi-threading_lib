#include "my_unique_lock.h"

MyUniqueLock::MyUniqueLock(MyMutex& mutex) : mutex_(mutex), locked_(false)
{
    lock();
}

MyUniqueLock::~MyUniqueLock()
{
    unlock();
}

MyUniqueLock::MyUniqueLock(MyUniqueLock&& other) noexcept : mutex_(other.mutex_), locked_(other.locked_)
{
    other.locked_ = false;
}

void MyUniqueLock::lock()
{
    if (!locked_)
    {
        mutex_.lock();
        locked_ = true;
    }
}

void MyUniqueLock::unlock()
{
    if (locked_)
    {
        mutex_.unlock();
        locked_ = false;
    }
}
