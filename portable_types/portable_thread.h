#ifndef MY_THREAD_PORTABLE_THREAD_H
#define MY_THREAD_PORTABLE_THREAD_H

#include <tuple>

#ifdef __linux
	#include <pthread.h>
	#include <unistd.h>
	#include <sched.h>
	typedef void* thread_routine;
	typedef void* mvoid;
#elif defined WIN32
	#include <windows.h>
	typedef DWORD thread_routine;
	typedef LPVOID mvoid;
#endif // __linux

template <typename Callable, typename... Args>
struct ThreadData
{
	Callable func;
	std::tuple<Args...> args;

	void invoke()
	{
		std::apply(func, args);
	}
};

template <typename Callable, typename... Args>
static thread_routine thread_start_routine(mvoid arg)
{
	auto* threadData = static_cast<ThreadData<Callable, Args...>*>(arg);
	threadData->invoke();
	delete threadData;
	return nullptr;
}

#ifdef __linux
	typedef pthread_t my_thread_t;
	typedef void** retval;

	template <typename Callable, typename... Args>
	my_thread_t thread_create(my_thread_t* handle, Callable&& func, Args&&... args)
	{
		auto threadData = new ThreadData<Callable, Args...>{std::forward<Callable>(func), std::forward_as_tuple(args...)};

		pthread_create(handle, NULL, thread_start_routine<Callable, Args...>, threadData);
		return *handle;
	}

	static void m_join(my_thread_t my_thread, retval val)
	{
		pthread_join(my_thread, val);
	}
	static void thread_destroy(my_thread_t my_thread)
	{
		//just a stub
	}
	static void thread_sleep(size_t milliseconds)
	{
		usleep(milliseconds * 1000);
	}
	static void my_yield()
	{
		sched_yield();
	}
	static pid_t my_get_thread_id()
	{
		return gettid();
	}
	static long my_hardware_concurrency()
	{
		return sysconf( _SC_NPROCESSORS_ONLN );
	}

#elif defined WIN32
	typedef HANDLE my_thread_t;
	typedef DWORD* retval;

	template <typename Callable, typename... Args>
	my_thread_t thread_create(my_thread_t handle, Callable&& func, Args&&... args)
	{
		auto threadData = new ThreadData<Callable, Args...>{std::forward<Callable>(func), std::forward_as_tuple(args...)};

		return CreateThread(nullptr, 0, thread_start_routine<Callable, Args...>, threadData, 0, 0);
	}

	static void m_join(my_thread_t my_thread, retval val)
	{
		WaitForSingleObject(my_thread, INFINITE);

	}
	static void thread_destroy(my_thread_t my_thread)
	{
		CloseHandle(my_thread);
	}
	void my_thread_sleep(size_t milliseconds)
	{
		 Sleep(milliseconds);
	}
	void yield()
	{
		SwitchToThread();
	}
#endif // __linux

#endif //MY_THREAD_PORTABLE_THREAD_H
