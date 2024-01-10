#include "my_future.h"
#include "my_promise.h"


MyFuture<void>::MyFuture(typename MyPromise<void>::State* state, MyMutex& mutex, MyCondVar& cond_var)
        : state_(state), mutex_(mutex), cond_var_(cond_var) {};

void MyFuture<void>::get() {
    MyUniqueLock lock(mutex_);
    if (state_->policy == LaunchPolicy::Deferred && !state_->is_ready) {
        try {
            function_();
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
}

void MyFuture<void>::set_function(std::function<void()> func) {
    function_ = std::move(func);
}

