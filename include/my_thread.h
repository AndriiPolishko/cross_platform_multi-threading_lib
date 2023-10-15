#ifndef TERM_PROJECT_MY_THREAD_H
#define TERM_PROJECT_MY_THREAD_H


#include <pthread.h>
#include <functional>

class MyThread
{
    pthread_t my_thread{};
public:
    MyThread() = default;


    MyThread(void (*func)());
    void join(void **retval = NULL);

};




#endif //TERM_PROJECT_MY_THREAD_H
