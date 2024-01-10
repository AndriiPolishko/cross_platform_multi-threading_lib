#include "my_thread_pool.h"
#include <iostream>
#include "my_mutex.h"

MyMutex outerMutex;

void square_task(int num) {
    {
		// For good-looking output
		outerMutex.lock();
        std::cout << "Thread ID: " << my_get_thread_id() << ", Square of " << num << ": " << num * num << std::endl;
		outerMutex.unlock();
    }
}

int main() {
    MyThreadPool threadPool;

    for (int i = 1; i <= 10; ++i) {
        threadPool.submit([i]() { square_task(i); });
    }
    return 0;
}
