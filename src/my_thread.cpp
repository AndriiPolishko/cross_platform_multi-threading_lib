#include "../include/my_thread.h"

MyThread::MyThread(void func())
{
    pthread_create(&my_thread, NULL, reinterpret_cast<void *(*)(void *)>(func), NULL);
}

void MyThread::join(void **retval)
{
    pthread_join(my_thread, retval);
}