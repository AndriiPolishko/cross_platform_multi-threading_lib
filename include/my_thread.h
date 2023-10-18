#ifndef TERM_PROJECT_MY_THREAD_H
#define TERM_PROJECT_MY_THREAD_H

#include <pthread.h>
#include <functional>
#include <tuple>

template <typename Callable, typename... Args>
struct ThreadData {
    Callable func;
    std::tuple<Args...> args;

    void invoke() {
        std::apply(func, args);
    }
};

class MyThread
{
    pthread_t my_thread{};

    template<typename Callable, typename... Args>
    static void* thread_start_routine(void* arg) {
        auto threadData = static_cast<ThreadData<Callable, Args...>*>(arg);
        threadData->invoke();
        delete threadData;
        return nullptr;
    }

public:
    MyThread() = default;

    template<typename Callable, typename ...Args>
    explicit MyThread(Callable&& func, Args&&... args);
    void join(void **retval = nullptr) const;
};

template<typename Callable, typename ...Args>
MyThread::MyThread(Callable&& func, Args&&... args)
{
    auto threadData = new ThreadData<Callable, Args...>{std::forward<Callable>(func), std::forward_as_tuple(args...)};
    pthread_create(&my_thread, NULL, thread_start_routine<Callable, Args...>, threadData);
}


class MyMutex
{
public:
	pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
	MyMutex() = default;

	void lock();
	void unlock();

	MyMutex(const MyMutex &) = delete;
	MyMutex& operator=(const MyMutex&) = delete;
};

#endif //TERM_PROJECT_MY_THREAD_H
