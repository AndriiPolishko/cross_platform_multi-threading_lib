#include <functional>

#include <iostream>
#include "my_thread.h"
#include "my_mutex.h"

int counter = 0;
MyMutex mutex;

void count()
{
	mutex.lock();
	for(int i = 0; i < 10; i++)
		std::cout << counter++ << std::endl;
	mutex.unlock();
}


int main()
{
	MyThread first(count);
	MyThread second(count);
	first.join();
	second.join();
    return 0;
}

