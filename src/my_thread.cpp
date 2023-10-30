#include "../include/my_thread.h"

void MyThread::join(retval val) const
{
	m_join(my_thread, val);
}

MyThread::~MyThread()
{
	thread_destroy(my_thread);
}
