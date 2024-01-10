#ifndef MY_THREAD_MY_THREAD_SAFE_QUEUE_H
#define MY_THREAD_MY_THREAD_SAFE_QUEUE_H

#include <memory>
#include <queue>
#include <functional>
#include "my_mutex.h"
#include "my_unique_lock.h"
#include "my_conditional_variable.h"
#include "my_lock_guard.h"


template <typename T>
class MyThreadSafeQueue {
public:
	MyThreadSafeQueue() = default;
	MyThreadSafeQueue(const MyThreadSafeQueue& anotherQueue)
	{
		MyLockGuard lockGuard(mutex_);
		queue_ = anotherQueue.queue_;
	}
	MyThreadSafeQueue operator=(const MyThreadSafeQueue&) = delete;

    void push(T value);
	bool try_pop(T& value);
	std::shared_ptr<T> try_pop();
	void wait_and_pop(T& value);
	std::shared_ptr<T> wait_and_pop();
    [[nodiscard]] bool empty();
    [[nodiscard]] size_t size();
private:
	MyMutex mutex_;
	std::queue<T> queue_;
	MyCondVar cond_;
};
#endif // MY_THREAD_MY_THREAD_SAFE_QUEUE_H