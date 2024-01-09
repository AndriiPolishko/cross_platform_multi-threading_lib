#include "my_promise.h"
#include "my_future.h"


MyPromise<void>::MyPromise(LaunchPolicy policy)
        : state_({.policy = policy}) {};

void MyPromise<void>::set_ready() {
    MyUniqueLock lock(mutex_);
    state_.is_ready = true;
    cond_var_.signal();
}

void MyPromise<void>::set_exception(const std::exception_ptr& e) {
    MyUniqueLock lock(mutex_);
    state_.exception = e;
    state_.is_ready = true;
    cond_var_.signal();
}

MyFuture<void> MyPromise<void>::get_future() {
    return {&state_, mutex_, cond_var_};
}
