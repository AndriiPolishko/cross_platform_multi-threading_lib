#include "my_mutex.h"

MyMutex::~MyMutex()
{
	clear_my_mutex(&my_mutex);
}

void MyMutex::lock()
{
	lock_my_mutex(&my_mutex);
}
void MyMutex::unlock()
{
	unlock_my_mutex(&my_mutex);
}
my_mutex_t* MyMutex::native_handle()
{
	return &my_mutex;
}