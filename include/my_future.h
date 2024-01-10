#ifndef MY_FUTURE_H
#define MY_FUTURE_H

#include "my_conditional_variable.h"
#include "my_mutex.h"
#include "my_promise.h"
#include "my_unique_lock.h"


template <> class MyFuture<void>;

template <typename T>
class MyFuture {
public:
    MyFuture(typename MyPromise<T>::State* state, MyMutex& mutex, MyCondVar& cond_var);
    T get();
    void set_function(std::function<T()> func);
private:
    typename MyPromise<T>::State* state_;
    MyMutex& mutex_;
    MyCondVar& cond_var_;
    std::function<T()> function_;
};


template <>
class MyFuture<void> {
public:
    MyFuture(typename MyPromise<void>::State* state, MyMutex& mutex, MyCondVar& cond_var);
    void get();
    void set_function(std::function<void()> func);
private:
    typename MyPromise<void>::State* state_;
    MyMutex& mutex_;
    MyCondVar& cond_var_;
    std::function<void()> function_;
};

template <typename T>
MyFuture<T>::MyFuture(typename MyPromise<T>::State* state, MyMutex& mutex, MyCondVar& cond_var)
        : state_(state), mutex_(mutex), cond_var_(cond_var) {};

template <typename T>
T MyFuture<T>::get() {
    MyUniqueLock lock(mutex_);
    if (state_->policy == LaunchPolicy::Deferred && !state_->is_ready) {
        try {
            state_->value = function_();
            state_->is_ready = true;
        } catch (...) {
            state_->exception = std::current_exception();
            state_->is_ready = true;
            std::rethrow_exception(state_->exception);
        }
    }

    while (!state_->is_ready) {
        cond_var_.wait(&mutex_);
    }

    if (state_->exception) {
        std::rethrow_exception(state_->exception);
    }

    return *state_->value;
}

template <typename T>
void MyFuture<T>::set_function(std::function<T()> func) {
    function_ = std::move(func);
}

#endif // MY_FUTURE_H

