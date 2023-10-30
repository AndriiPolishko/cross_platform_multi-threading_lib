#ifndef MY_THREAD_PORTABLE_COND_VAR_H
#define MY_THREAD_PORTABLE_COND_VAR_H

#ifdef __linux
#include <pthread.h>
typedef pthread_cond_t my_cond;

static void cv_init(my_cond* my_cv)
{
	pthread_cond_init(my_cv, nullptr);
}
void cv_destroy(my_cond* my_cv)
{
	pthread_cond_destroy(my_cv);
}
void cv_signal(my_cond* my_cv)
{
	pthread_cond_signal(my_cv);
}
void cv_wait(my_cond* my_cv, pthread_mutex_t* mutex)
{
	pthread_cond_wait(my_cv, mutex);
}


#elif defined WIN32

#endif //__linux

#endif //MY_THREAD_PORTABLE_COND_VAR_H
