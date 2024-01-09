#ifndef MY_PROMISE_H
#define MY_PROMISE_H

#include <optional>
#include <functional>

#include "my_conditional_variable.h"
#include "my_mutex.h"
#include "my_unique_lock.h"
#include "launch_policy.h"

template <typename T> class MyFuture;

template <typename T>
class MyPromise {
public:
    explicit MyPromise(LaunchPolicy policy = LaunchPolicy::Immediate);

    void set_value(T value);

    void set_exception(const std::exception_ptr& e);

    MyFuture<T> get_future();

private:
    struct State {
        bool is_ready = false;
        std::optional<T> value;
        std::exception_ptr exception;
        LaunchPolicy policy;
    };

    State state_;
    MyMutex mutex_;
    MyCondVar cond_var_;

    friend class MyFuture<T>;
};


template <>
class MyPromise<void> {
public:
    explicit MyPromise(LaunchPolicy policy = LaunchPolicy::Immediate);

    void set_ready();

    void set_exception(const std::exception_ptr& e);

    MyFuture<void> get_future();

private:
    struct State {
        bool is_ready = false;
        std::exception_ptr exception;
        LaunchPolicy policy;
    };

    State state_;
    MyMutex mutex_;
    MyCondVar cond_var_;

    friend class MyFuture<void>;
};


template <typename T>
MyPromise<T>::MyPromise(LaunchPolicy policy)
        : state_({.policy = policy}) {};

template <typename T>
void MyPromise<T>::set_value(T value) {
    MyUniqueLock lock(mutex_);
    state_.value = std::move(value);
    state_.is_ready = true;
    cond_var_.signal();
}

template <typename T>
void MyPromise<T>::set_exception(const std::exception_ptr& e) {
    MyUniqueLock lock(mutex_);
    state_.exception = e;
    state_.is_ready = true;
    cond_var_.signal();
}

template <typename T>
MyFuture<T> MyPromise<T>::get_future() {
    return MyFuture<T>(&state_, mutex_, cond_var_);
}

#endif // MY_PROMISE_H