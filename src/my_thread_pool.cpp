#include "my_thread_pool.h"

MyThreadPool::MyThreadPool() : done(false), joiner_(threads_)
{
	unsigned const thread_count = my_hardware_concurrency();
	try
	{
		for (unsigned i = 0; i < thread_count; ++i)
		{
			MyThread tmp {&MyThreadPool::worker_thread,this};
			threads_.push_back(tmp);
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
	while (!done || !work_queue_.empty())
	{
		std::function<void()> task;
		if (work_queue_.try_pop(task))
		{
			task();
			if (work_queue_.empty()) {
				notify_all_tasks_done();
			}
		} else {
			my_yield();
		}
	}
}

void MyThreadPool::notify_all_tasks_done() {
	mutex_.lock();
	cond_.signal(); // Notify that all tasks are done
	mutex_.unlock();
}

MyThreadPool::~MyThreadPool() {
	mutex_.lock();
	while (!work_queue_.empty()) {
		cond_.wait(&mutex_);
	}
	done = true;
	mutex_.unlock();
}