#ifndef TERM_PROJECT_MY_THREAD_H
#define TERM_PROJECT_MY_THREAD_H

#include "../portable_types/portable_thread.h"

class MyThread
{
public:
    MyThread() = default;
    ~MyThread();

    template <typename Callable, typename... Args>
    explicit MyThread(Callable&& func, Args&&... args)
    {
        my_thread_create(std::forward<Callable>(func), std::forward<Args>(args)...);
    }

    void join(retval val = nullptr) const;
    void detach() const;

    template <typename Callable, typename... Args>
    void my_thread_create(Callable&& func, Args&&... args)
    {
        my_thread = thread_create(&my_thread, std::forward<Callable>(func), std::forward<Args>(args)...);
    }

    my_thread_t native_handle() const { return my_thread; }

private:
    my_thread_t my_thread{};
};

#endif // TERM_PROJECT_MY_THREAD_H
