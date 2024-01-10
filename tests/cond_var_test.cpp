#include <iostream>
#include <queue>

#include "my_thread.h"
#include "my_mutex.h"
#include "my_conditional_variable.h"

std::queue<int> dataQueue;
MyMutex mutex;
MyCondVar condVar;

void* producer() {
	for (int i = 0; i < 10; ++i) {
		mutex.lock();
		while (!dataQueue.empty()) {
			condVar.wait(&mutex);
		}
		dataQueue.push(i);
		std::cout << "Produced: " << i << std::endl;
		condVar.signal();
		mutex.unlock();
	}
	return nullptr;
}


void* consumer() {
	for (int i = 0; i < 10; ++i) {
		mutex.lock();
		while (dataQueue.empty()) {
			condVar.wait(&mutex);
		}
		int value = dataQueue.front();
		dataQueue.pop();
		std::cout << "Consumed: " << value << std::endl;
		condVar.signal();
		mutex.unlock();
	}
	return nullptr;
}

int main()
{
	MyThread prodThread, consThread;
	prodThread.my_thread_create(producer);
	consThread.my_thread_create(consumer);

	prodThread.join();
	consThread.join();
	return 0;
}