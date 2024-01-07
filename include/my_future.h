#ifndef MY_FUTURE_H
#define MY_FUTURE_H

#include <string>
#include <optional>
#include <exception>

#include "my_conditional_variable.h"
#include "my_mutex.h"
#include "my_promise.h"
#include "my_unique_lock.h"
#include "my_promise.h"
#include "my_unique_lock.h"


template <typename T>
class MyFuture {
public:
    MyFuture(typename MyPromise<T>::State* state, MyMutex& mutex, MyCondVar& cond_var);

    T get();

private:
    typename MyPromise<T>::State* state_;
    MyMutex& mutex_;
    MyCondVar& cond_var_;
};

template <typename T>
MyFuture<T>::MyFuture(typename MyPromise<T>::State* state, MyMutex& mutex, MyCondVar& cond_var)
        : state_(state), mutex_(mutex), cond_var_(cond_var) {}

template <typename T>
T MyFuture<T>::get() {
    MyUniqueLock lock(mutex_);
    cond_var_.wait(mutex_);

    if (state_->exception) {
        std::rethrow_exception(state_->exception);
    }

    return *state_->value;
}

#endif // MY_FUTURE_H

