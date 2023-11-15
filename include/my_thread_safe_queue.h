#ifndef MY_THREAD_MY_THREAD_SAFE_QUEUE_H
#define MY_THREAD_MY_THREAD_SAFE_QUEUE_H

#include <queue>
#include <condition_variable>
#include <functional>
#include "my_mutex.h"
#include "my_unique_lock.h"
#include "my_conditional_variable.h"



template <typename T>
class MyThreadSafeQueue {
private:
    std::queue<T> queue_;
    MyMutex mutex_;
    MyCondVar cond_;

public:
    void enqueue(const T& value);
    T dequeue();
//    bool try_pop(std::function<void()>& task);
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] size_t size() const;
};
#endif // MY_THREAD_MY_THREAD_SAFE_QUEUE_H