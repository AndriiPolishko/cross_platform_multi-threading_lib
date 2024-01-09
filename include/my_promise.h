#ifndef MY_PROMISE_H
#define MY_PROMISE_H

#include <optional>
#include <exception>
#include <string>
#include "my_conditional_variable.h"
#include "my_mutex.h"
#include "my_unique_lock.h"

template <typename T> class MyFuture;

template <typename T>
class MyPromise {
public:
    MyPromise();

    void set_value(T value);
    void set_exception(const std::exception_ptr& e);
    MyFuture<T> get_future();

private:
    struct State {
        bool is_ready = false;
        std::optional<T> value;
        std::exception_ptr exception;
    };

    State state_;
    MyMutex mutex_;
    MyCondVar cond_var_;

    friend class MyFuture<T>;
};

#include "my_future.h"

template <typename T>
MyPromise<T>::MyPromise() = default;

template <typename T>
void MyPromise<T>::set_value(T value) {
    {
        MyUniqueLock lock(mutex_);
        state_.value = std::move(value);
        state_.is_ready = true;
    }
    cond_var_.signal();
}

template <typename T>
void MyPromise<T>::set_exception(const std::exception_ptr& e) {
    {
        MyUniqueLock lock(mutex_);
        state_.exception = e;
        state_.is_ready = true;
    }
    cond_var_.signal();
}

template <typename T>
MyFuture<T> MyPromise<T>::get_future() {
    return MyFuture<T>(&state_, mutex_, cond_var_);
}

#endif // MY_PROMISE_H
