#include "my_thread.h"
#include "my_mutex.h"
#include "my_unique_lock.h"
#include <thread>
#include <iostream>


void increment_shared_resource(int& shared_resource, MyMutex& mutex) {
    MyUniqueLock lock(mutex);
    shared_resource++;
}

void test_thread_safety() {
    MyMutex mutex;
    int shared_resource = 0;


    MyThread thread1{};
    MyThread thread2{};

    thread1.my_thread_create(increment_shared_resource, std::ref(shared_resource), std::ref(mutex));
    thread2.my_thread_create(increment_shared_resource, std::ref(shared_resource), std::ref(mutex));

    thread1.join();
    thread2.join();

    std::cout << "shared_resource should be 2 here." << std::endl;
    std::cout << shared_resource << std::endl;
}


int main()
{
    test_thread_safety();
    return 0;
}