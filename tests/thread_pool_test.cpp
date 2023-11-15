#include "my_thread_pool.h"
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>

std::mutex cout_mutex; // Mutex to protect std::cout

// Function to be executed concurrently
void square_task(int num) {
    {
        std::lock_guard<std::mutex> lock(cout_mutex); // Lock the mutex
        std::cout << "Thread ID: " << std::this_thread::get_id() << ", Square of " << num << ": " << num * num << std::endl;
    } // lock goes out of scope, releasing the lock
}

int main() {
    const int numTasks = 10;
    const int threadCount = HW_CONCURRENCY;

    MyThreadPool threadPool;

    // Submit tasks to the thread pool
    for (int i = 1; i <= numTasks; ++i) {
        threadPool.submit([i] { square_task(i); });
    }

    // Main thread may do some work while worker threads are running

    // Join threads in the thread pool
    // This is important to wait for all tasks to complete before exiting the program
    // If not joined, the threads may be terminated abruptly
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulating main thread doing some work
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Main thread is still doing some work..." << std::endl;
    }

    // The destructor of MyThreadPool will ensure that all threads are joined
    // before the MyThreadPool object goes out of scope

    return 0;
}
