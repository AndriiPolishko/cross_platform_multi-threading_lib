#ifndef MY_THREAD_MY_JOINER_H
#define MY_THREAD_MY_JOINER_H

#include "my_thread.h"
#include <vector>
#include <pthread.h>

class MyJoiner
{
	std::vector<MyThread>& threads;
public:
	explicit MyJoiner(std::vector<MyThread>& threads_):
			threads(threads_)
	{}
	~MyJoiner()
	{
		for(MyThread& thread : threads)
		{
			thread.join();
		}
	}
};


#endif //MY_THREAD_MY_JOINER_H
