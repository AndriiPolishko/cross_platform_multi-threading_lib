#include <functional>

#include <iostream>
#include "my_thread.h"
#include "my_mutex.h"
#include  "my_conditional_variable.h"

#define NUM_THREADS 3
#define TCOUNT 10
#define COUNT_LIMIT 12

int count = 0;
int thread_ids[3] = {0,1,2};
MyMutex count_mutex;
MyCondVar count_threshold_cv;
void inc_count();
void watch_count();


int main()
{
	long t1=1, t2=2, t3=3;
	MyThread threads[3];
	threads[0].my_thread_create(watch_count);
	threads[1].my_thread_create(inc_count);
	threads[2].my_thread_create(inc_count);
	for (int i=0; i<NUM_THREADS; i++) {
		threads[i].join();
	}

	std::cout << count;
    return 0;
}

void inc_count(){
	for (int i=0; i<TCOUNT; i++) {
		count_mutex.lock();
		count++;
		if (count == COUNT_LIMIT) {count_threshold_cv.signal(); }
		count_mutex.unlock();
	}
	pthread_exit(NULL);
}
void watch_count(){
	count_mutex.lock();
	if (count<COUNT_LIMIT) {
		count_threshold_cv.wait(count_mutex.native_handle());
		count += 125;
	}
	count_mutex.unlock();
	pthread_exit(NULL);
}
