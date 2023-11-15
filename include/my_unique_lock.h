#ifndef MY_THREAD_MY_UNIQUE_LOCK_H
#define MY_THREAD_MY_UNIQUE_LOCK_H

#include "my_mutex.h"

class MyUniqueLock {
public:
    explicit MyUniqueLock(const MyMutex& m) : mutex_(const_cast<MyMutex &>(m)) {
        lock();
    }

    ~MyUniqueLock() {
        unlock();
    }

    MyUniqueLock(const MyUniqueLock&) = delete;
    MyUniqueLock& operator=(const MyUniqueLock&) = delete;

    MyUniqueLock(MyUniqueLock&& other) noexcept : mutex_(other.mutex_), locked_(other.locked_) {
        other.locked_ = false;
    }

    MyUniqueLock& operator=(MyUniqueLock&& other) noexcept {
        if (this != &other) {
            unlock();
            mutex_ = other.mutex_;
            locked_ = other.locked_;
            other.locked_ = false;
        }
        return *this;
    }

    void lock() {
        if (!locked_) {
            mutex_.lock();
            locked_ = true;
        }
    }

    void unlock() {
        if (locked_) {
            mutex_.unlock();
            locked_ = false;
        }
    }

private:
    MyMutex& mutex_;
    bool locked_{};
};

#endif // MY_THREAD_MY_UNIQUE_LOCK_H
