#ifndef MY_THREAD_MY_THREAD_POOL_H
#define MY_THREAD_MY_THREAD_POOL_H

#include <atomic>
#include <functional>
#include "my_thread.h"
#include "my_thread_safe_queue.h"

#define HW_CONCURRENCY 4

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
    std::atomic_bool done;
    MyThreadSafeQueue<std::function<void()>> work_queue;
    std::vector<MyThread> threads;
    join_threads joiner;

    void worker_thread()
    {
        while (!done)
        {
            std::function<void()> task;
//            if (work_queue.try_pop(task))
//            {
//                task();
//            }

            if (!work_queue.isEmpty()) {
                task = work_queue.dequeue();
                task();
            } else {
                // You may replace this with your platform-specific yield function
                // e.g., my_yield_function();
                // MyThread::yield();
            }
        }
    }

public:
    MyThreadPool() : done(false), joiner(threads)
    {

        unsigned const thread_count = HW_CONCURRENCY;
        try
        {
            for (unsigned i = 0; i < thread_count; ++i)
            {
                MyThread thread{};
                thread.my_thread_create(&MyThreadPool::worker_thread, this);
                threads.emplace_back(thread);
            }
        }
        catch (...)
        {
            done = true;
            throw;
        }
    }

    ~MyThreadPool()
    {
        done = true;
    }

    template <typename FunctionType>
    void submit(FunctionType f)
    {
        work_queue.enqueue(std::function<void()>(f));
    }
};
#endif //MY_THREAD_MY_THREAD_POOL_H
