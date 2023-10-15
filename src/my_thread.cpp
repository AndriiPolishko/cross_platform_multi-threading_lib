#include "../include/my_thread.h"

void MyThread::join(void **retval)
{
    pthread_join(my_thread, retval);
}
