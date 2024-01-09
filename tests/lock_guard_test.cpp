#include <iostream>
#include "my_lock_guard.h"
#include "my_thread.h"

int counter = 0;

MyMutex counterMutex{};

void count_10()
{
	MyLockGuard lg{counterMutex};
	for(size_t i = 0; i < 10; i++)
		std::cout << counter++ << std::endl;
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
