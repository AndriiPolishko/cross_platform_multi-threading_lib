#include "my_thread_safe_queue.h"

template class MyThreadSafeQueue<int>;
template class MyThreadSafeQueue<std::function<void()>>;
template class MyThreadSafeQueue<std::string>;

template<typename T>
void MyThreadSafeQueue<T>::enqueue(const T& value) {
    MyUniqueLock lock(mutex_);
    queue_.push(value);
    cond_.signal();
}

template<typename T>
T MyThreadSafeQueue<T>::dequeue() {
    cond_.enter_critical_section();
    while (queue_.empty()) {
        cond_.wait();
    }

    T value = queue_.front();
    queue_.pop();
    cond_.leave_critical_section();
    return value;
}

//template<typename T>
//bool MyThreadSafeQueue<T>::try_pop(std::function<void()>& task) {
//    MyUniqueLock lock(mutex_);
//
//    if (queue_.empty()) {
//        return false;  // Queue is empty, no task to pop.
//    }
//
//    // Retrieve the task from the front of the queue.
//    task = queue_.front();
//    queue_.pop();
//    return true;  // Task successfully popped.
//}
//

template<typename T>
bool MyThreadSafeQueue<T>::isEmpty() const {
    MyUniqueLock lock(mutex_);
    return queue_.empty();
}

template<typename T>
size_t MyThreadSafeQueue<T>::size() const {
    MyUniqueLock lock(mutex_);
    return queue_.size();
}
