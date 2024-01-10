#include <iostream>
#include "../include/my_thread_safe_queue.h"
#include "../include/my_thread.h"

MyThreadSafeQueue<int> queue;

const int END = 10;

void producer(int start, int end = END) {
    for (int i = start; i <= end; ++i) {
        queue.push(i);
		std::cout << "Enqueued: " << i << std::endl;
    }
}

void consumer(int num_elements) {
	while (true)
	{
		int data;
		queue.wait_and_pop(data);
		std::cout << "Dequeued: " << data << std::endl;

		if (data == num_elements)
		{
			break;
		}
	}
}

int main() {

    MyThread thread1{};
    MyThread thread2{};
    thread1.my_thread_create(producer, 1, END);
	thread2.my_thread_create(consumer, END);

	thread1.join();
    thread2.join();

    return 0;
}
