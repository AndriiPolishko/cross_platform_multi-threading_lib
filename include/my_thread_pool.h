#ifndef MY_THREAD_MY_THREAD_POOL_H
#define MY_THREAD_MY_THREAD_POOL_H

#include <atomic>
#include <functional>
#include "my_thread.h"
#include "my_mutex.h"
#include "my_conditional_variable.h"
#include "my_thread_safe_queue.h"

class join_threads
{
public:
    explicit join_threads(std::vector<MyThread>& threads):
			threads_(threads)
    {}
    ~join_threads()
    {
        for(const auto & thread : threads_)
        {
            thread.join();
        }
    }
private:
	std::vector<MyThread>& threads_;
};

class MyThreadPool
{
public:
    MyThreadPool();
    ~MyThreadPool();

    template <typename FunctionType>
    void submit(FunctionType f);

private:
	void notify_all_tasks_done();

private:
	std::atomic_bool done;
	MyThreadSafeQueue<std::function<void()>> work_queue_;
	std::vector<MyThread> threads_;
	join_threads joiner_;
	MyCondVar cond_;
	MyMutex mutex_;
private:
	void worker_thread();
};

template <typename FunctionType>
void MyThreadPool::submit(FunctionType f)
{
	work_queue_.push(std::function<void()>(f));
}

#endif //MY_THREAD_MY_THREAD_POOL_H
