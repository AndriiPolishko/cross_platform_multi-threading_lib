//
// Created by polis on 30.10.2023.
//

#ifndef MY_THREAD_PORTABLE_MUTEX_H
#define MY_THREAD_PORTABLE_MUTEX_H

#ifdef __linux
	#include <pthread.h>
	typedef pthread_mutex_t my_mutex_t;

	static my_mutex_t create_mutex()
	{
		return PTHREAD_MUTEX_INITIALIZER;
	}
	static void lock_my_mutex(my_mutex_t* my_mutex)
	{
		pthread_mutex_lock(my_mutex);
	}
	static bool unlock_my_mutex(my_mutex_t* my_mutex)
	{
		pthread_mutex_unlock(my_mutex);
	}
	static void clear_my_mutex(my_mutex_t* my_mutex)
	{
		pthread_mutex_destroy(my_mutex);
	}
#elif defined WIN32
	#include <Windows.h>
	typedef HANDLE my_mutex_t;

	static my_mutex_t create_mutex()
	{
		return CreateMutex(NULL, FALSE, NULL);
	}
	static void lock_my_mutex(my_mutex_t* my_mutex)
	{
		WaitForSingleObject(*my_mutex, INFINITE);
	}
	static bool unlock_my_mutex(my_mutex_t* my_mutex)
	{
		return ReleaseMutex(*my_mutex);
	}
	static void clear_my_mutex(my_mutex_t my_mutex)
	{
		CloseHandle(my_mutex);
	}

#endif // __linux

#endif //MY_THREAD_PORTABLE_MUTEX_H
