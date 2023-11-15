#include <iostream>
#include "../include/my_thread_safe_queue.h"
#include "../include/my_thread.h"


void producer(MyThreadSafeQueue<int>& queue, int start, int end) {
    for (int i = start; i <= end; ++i) {
        queue.enqueue(i);
    }
}

void consumer(MyThreadSafeQueue<int>& queue, int num_elements) {
    for (int i = 0; i < num_elements; ++i) {
        int value = queue.dequeue();
        std::cout << "Dequeued: " << value << std::endl;
    }
}

int main() {
    MyThreadSafeQueue<int> myQueue;

    MyThread thread1{};
    MyThread thread2{};
    thread1.my_thread_create(producer, std::ref(myQueue), 1, 10);
    thread2.my_thread_create(consumer, std::ref(myQueue), 10);

    thread1.join();
    thread2.join();

    return 0;
}
