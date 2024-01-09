#include "my_thread.h"
#include "my_future.h"
#include "my_promise.h"
#include "launch_policy.h"

#include <condition_variable>


template<typename ReturnType, typename Function>
void execute_and_set_promise(std::shared_ptr<MyPromise<ReturnType>> promise, Function&& func) {
    try {
        auto result = func();
        promise->set_value(result);
    } catch (...) {
        promise->set_exception(std::current_exception());
    }
}

template<typename Function>
void execute_and_set_promise(std::shared_ptr<MyPromise<void>> promise, Function&& func) {
    try {
        func();
        promise->set_ready();
    } catch (...) {
        promise->set_exception(std::current_exception());
    }
}

template<typename F, typename... Args>
auto my_async(LaunchPolicy policy, F&& f, Args&&... args) {

    using return_type = std::invoke_result_t<F, Args...>;

    auto promise = std::make_shared<MyPromise<return_type>>(policy);
    auto future = promise->get_future();
    auto bound_function = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

    if (policy == LaunchPolicy::Immediate) {
        MyThread([promise, bound_function]() mutable {
            try {
                execute_and_set_promise(promise, bound_function);
            } catch (...) {
                promise->set_exception(std::current_exception());
            }
        }).detach();
    } else {
        future.set_function(bound_function);
    }

    return future;
}

template<typename F, typename... Args>
auto my_async(F&& f, Args&&... args) {
    return my_async(LaunchPolicy::Immediate, std::forward<F>(f), std::forward<Args>(args)...);
}