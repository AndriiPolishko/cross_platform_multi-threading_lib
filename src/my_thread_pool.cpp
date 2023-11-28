#include "my_thread_pool.h"

MyThreadPool::MyThreadPool() : done(false), joiner(threads)
{
	unsigned const thread_count = my_hardware_concurrency();
	try
	{
		for (unsigned i = 0; i < thread_count; ++i)
		{
			MyThread tmp {&MyThreadPool::worker_thread,this};
			threads.push_back(tmp);
		}
	}
	catch (...)
	{
		done = true;
		throw;
	}
}

void MyThreadPool::worker_thread()
{
	while (!done)
	{
		std::function<void()> task;
		if (work_queue.try_pop(task))
		{
			task();
		} else {
			my_yield();
		}
	}
}
