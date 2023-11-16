#include "my_thread_safe_queue.h"

template<typename T>
void MyThreadSafeQueue<T>::enqueue(const T& value)
{
    MyUniqueLock lock(mutex_);
    queue_.push(value);
    cond_.signal();
}

template<typename T>
T MyThreadSafeQueue<T>::dequeue()
{
    MyUniqueLock lock(mutex_);
    while (queue_.empty())
    {
        cond_.wait();
    }

    T value = queue_.front();
    queue_.pop();
    return value;
}

template<typename T>
bool MyThreadSafeQueue<T>::try_pop(T& task)
{
    MyUniqueLock lock(mutex_);

    if (queue_.empty())
    {
        return false;
    }

    task = queue_.front();
    queue_.pop();
    return true;
}


template<typename T>
bool MyThreadSafeQueue<T>::isEmpty()
{
    MyUniqueLock lock(mutex_);
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

