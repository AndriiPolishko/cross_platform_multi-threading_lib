#ifndef MY_THREAD_MY_THREAD_POOL_H
#define MY_THREAD_MY_THREAD_POOL_H

#include <atomic>
#include <functional>
#include "my_thread.h"
#include "my_thread_safe_queue.h"

class join_threads
{
    std::vector<MyThread>& threads;
public:
    explicit join_threads(std::vector<MyThread>& threads_):
            threads(threads_)
    {}
    ~join_threads()
    {
        for(const auto & thread : threads)
        {
            thread.join();
        }
    }
};

class MyThreadPool
{
public:
    MyThreadPool();

    ~MyThreadPool() {
			done = true;
	}

    template <typename FunctionType>
    void submit(FunctionType f);
private:
	std::atomic_bool done;
	MyThreadSafeQueue<std::function<void()>> work_queue;
	std::vector<MyThread> threads;
	join_threads joiner;
private:
	void worker_thread();
};

template <typename FunctionType>
void MyThreadPool::submit(FunctionType f)
{
	work_queue.enqueue(std::function<void()>(f));
}

#endif //MY_THREAD_MY_THREAD_POOL_H
