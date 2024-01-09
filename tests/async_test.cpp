#include <iostream>

#include "my_thread.h"
#include "my_promise.h"
#include "my_future.h"
#include "my_async.h"

int count(int a) {
    return a * a;
}

void test1() {
    auto future = my_async(count, 6);
    std::cout << future.get() << std::endl;
}

int fail_function(int a) {
    throw std::runtime_error("Error in thread");
    return a * a;
}

void test_exception_handling() {
    auto future = my_async(fail_function, 5);
    try {
        std::cout << future.get() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

void test_multiple_async_calls() {
    auto future1 = my_async(count, 5);
    auto future2 = my_async(count, 10);

    // Do some other work here
    sleep(1);

    // Then, get the results
    std::cout << "Result 1: " << future1.get() << std::endl;
    std::cout << "Result 2: " << future2.get() << std::endl;
}


void test_direct_promise_future() {
    MyPromise<int> promise;
    MyFuture<int> future = promise.get_future();

    // Fulfill the promise in a separate thread
    MyThread tread{};

    tread.my_thread_create([&promise]() {
        promise.set_value(42);
    });

    std::cout << "Result: " << future.get() << std::endl;

    tread.join();
}


struct ComplexData {
    int a;
    std::string b;
};

ComplexData process_complex_data(const ComplexData& data) {
    ComplexData result = {data.a * 2, data.b + " processed"};
    return result;
}

void test_complex_data() {
    ComplexData data = {10, "test"};
    auto future = my_async(process_complex_data, data);
    ComplexData result = future.get();
    std::cout << "Result: " << result.a << ", " << result.b << std::endl;
}

int increase_value(int value) {
    sleep(1); // Simulate work
    value += 1;
    return value;
}

void test_deferred_execution() {
    int test_var = 0;
    auto future = my_async(LaunchPolicy::Deferred, increase_value, test_var);

    auto a = future.get();
    std::cout << "Result: " << a << std::endl;
}

void do_work() {
    sleep(1);
    std::cout << "Work done" << std::endl;

}

void test_void() {
    auto future = my_async(LaunchPolicy::Deferred, do_work);

    future.get();
}

int main() {

    test1();
    test_exception_handling();
    test_multiple_async_calls();
    test_direct_promise_future();
    test_complex_data();
    test_deferred_execution();
    test_void();

    return 0;
}
