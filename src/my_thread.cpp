#include "../include/my_thread.h"

void MyThread::join(void **retval) const {
    pthread_join(my_thread, retval);
}
