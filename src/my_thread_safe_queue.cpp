#include "my_thread_safe_queue.h"

template<typename T>
void MyThreadSafeQueue<T>::push(const T value)
{
	MyLockGuard lockGuard(mutex_);
    queue_.push(value);
    cond_.signal();
}

template<typename T>
void  MyThreadSafeQueue<T>::wait_and_pop(T& value)
{
	mutex_.lock();
	while (queue_.empty()) {
		cond_.wait(&mutex_);
	}
	value = queue_.front();
	queue_.pop();
	if (queue_.empty()) {
		cond_.signal();
	}
	mutex_.unlock();
}

template<typename T>
std::shared_ptr<T> MyThreadSafeQueue<T>::wait_and_pop()
{
	mutex_.lock();
	while (queue_.empty()) {
		cond_.wait(&mutex_);
	}
	std::shared_ptr<T> res = (std::make_shared<T>(queue_.front()));
	queue_.pop();
	if (queue_.empty()) {
		cond_.signal();
	}
	mutex_.unlock();
	return res;
}

template<typename T>
bool MyThreadSafeQueue<T>::try_pop(T& value)
{
	MyLockGuard lock(mutex_);

    if (queue_.empty())
    {
		return false;
	}

    value = queue_.front();
    queue_.pop();
    return true;
}

template<typename T>
std::shared_ptr<T> MyThreadSafeQueue<T>::try_pop()
{
	MyLockGuard lockGuard(mutex_);
	if(queue_.empty())
		return std::shared_ptr<T>();
	std::shared_ptr<T> res(std::make_shared<T>(queue_.front()));
	queue_.pop();
	return res;
}


template<typename T>
bool MyThreadSafeQueue<T>::empty()
{
    MyLockGuard lock(mutex_);
    return queue_.empty();
}

template<typename T>
size_t MyThreadSafeQueue<T>::size()
{
    MyUniqueLock lock(mutex_);
    return queue_.size();
}

template class MyThreadSafeQueue<int>;  // Explicit instantiation for int (or any other types you use)
template class MyThreadSafeQueue<std::function<void()>>;  // Explicit instantiation for std::function<void()> (or any other types you use)

