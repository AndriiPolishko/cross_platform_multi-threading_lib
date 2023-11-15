#include "my_thread.h"
#include "my_mutex.h"
#include <iostream>
int counter = 1;

MyMutex counter_mutex;

void count_10()
{
	counter_mutex.lock();
	for(size_t i = 0; i < 10; i++)
		std::cout << counter++ << std::endl;
	counter_mutex.unlock();
}

int main()
{
	MyThread thread1{};
	MyThread thread2{};
	thread1.my_thread_create(count_10);
	thread2.my_thread_create(count_10);

	thread1.join();
	thread2.join();
}