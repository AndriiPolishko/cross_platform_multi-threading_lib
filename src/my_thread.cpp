#include "../include/my_thread.h"

void MyThread::join(void **retval) const {
    pthread_join(my_thread, retval);
}

void MyMutex::lock()
{
	pthread_mutex_lock(&my_mutex);
}
void MyMutex::unlock()
{
	pthread_mutex_unlock(&my_mutex);
}
