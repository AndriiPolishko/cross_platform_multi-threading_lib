#ifndef MY_THREAD_PORTABLE_COND_VAR_H
#define MY_THREAD_PORTABLE_COND_VAR_H

#if defined(__linux) || defined(__MACH__)
	#include <pthread.h>

	typedef pthread_mutex_t my_predicate;
	typedef pthread_cond_t my_cond;

	// Initialise conditional variables
	static void cv_init(my_cond* my_cv)
	{
		pthread_cond_init(my_cv, nullptr);
	}

	// Destroy conditional variable
	static void cv_destroy(my_cond* my_cv)
	{
		pthread_cond_destroy(my_cv);
	}

	// Unblock specific thread
	static void cv_signal(my_cond* my_cv)
	{
		pthread_cond_signal(my_cv);
	}

	// Unblock all threads
    static void cv_broadcast(my_cond* my_cv)
    {
        pthread_cond_broadcast(my_cv);
    }

	// Block on conditional variable
	static void cv_wait(my_cond* my_cv, pthread_mutex_t* mutex)
	{
		pthread_cond_wait(my_cv, mutex);
	}

#elif defined WIN32
	#include <Windows.h>
	typedef CRITICAL_SECTION my_predicate;
	typedef CONDITION_VARIABLE my_cond;

	static void cv_init(my_cond* my_cv)
	{
		// a stud
	}

	static void cv_destroy(my_cond* my_cv)
	{
		// a stud
	}

	static void cv_signal(my_cond* my_cv)
	{
		WakeConditionVariable(my_cv);
	}

	static void cv_wait(my_cond* my_cv, my_predicate* predicate)
	{
		SleepConditionVariableCS(my_cv, predicate, INFINITE);
	}
#endif //__linux

#endif //MY_THREAD_PORTABLE_COND_VAR_H
