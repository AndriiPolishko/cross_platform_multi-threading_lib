#include <iostream>
#include <condition_variable> // for make_shared
#include <optional>
#include <utility>

#include "my_thread.h"
#include "my_promise.h"
#include "my_future.h"

template<typename F, typename... Args>
auto my_async(F&& f, Args&&... args) {
    using return_type = decltype(f(args...));

    auto promise = std::make_shared<MyPromise<return_type>>();

    MyFuture<return_type> future = promise->get_future();

    MyThread([promise, f, args...]() mutable {
        try {
            // Set the value in the promise
            promise->set_value(f(std::forward<Args>(args)...));
        } catch (...) {
            // If an exception occurs, store it in the promise
            promise->set_exception(std::current_exception());
        }
    }).detach();

    return future;
}