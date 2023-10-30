#include "../include/my_thread.h"

void MyThread::join(void **retval) const {
	m_join(my_thread, retval);
}

//
