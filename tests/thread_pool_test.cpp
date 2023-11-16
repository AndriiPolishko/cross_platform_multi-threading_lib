#include "my_thread_pool.h"
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>

void square_task(int num) {
    {
        std::cout << "Thread ID: " << std::this_thread::get_id() << ", Square of " << num << ": " << num * num << std::endl;
    }
}

int main() {
    MyThreadPool threadPool;

    // Submit tasks to the pool
//    for (int i = 1; i <= 10; ++i) {
//        threadPool.submit([i]() { square_task(i); });
//    }

    // Allow some time for the threads to execute
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Interrupt and join the threads before the pool goes out of scope
//    threadPool.interrupt_and_join();

    return 0;
}
