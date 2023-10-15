#ifndef TERM_PROJECT_MY_THREAD_H
#define TERM_PROJECT_MY_THREAD_H



#include <pthread.h>
#include <functional>

template <typename Callable, typename... Args>
struct ThreadData {
    Callable func;
    std::tuple<Args...> args;
};

class MyThread
{
    pthread_t my_thread{};
public:
    MyThread() = default;
    template<typename Callable, typename ...Args>
    explicit MyThread(Callable&& func, Args&&... args);

    void join(void **retval = NULL);

};

template<typename Callable, typename ...Args>
MyThread::MyThread(Callable&& func, Args&&... args)
{
    auto threadData = new ThreadData<Callable, Args...>{std::forward<Callable>(func), std::forward_as_tuple(args...)};
    pthread_create(&my_thread, NULL, reinterpret_cast<void *(*)(void *)>(func), threadData);
}

#endif //TERM_PROJECT_MY_THREAD_H
