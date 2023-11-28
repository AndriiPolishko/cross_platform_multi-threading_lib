#include <iostream>
#include "my_thread.h"
#include "my_mutex.h"
#include  "my_conditional_variable.h"

int NUM_THREADS = 3;
int TCOUNT = 10;
int COUNT_LIMIT = 12;

int count = 0;
MyCondVar count_threshold_cv;
void inc_count();
void watch_count();


int main()
{
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
		count_threshold_cv.enter_critical_section();
		count++;
		if (count == COUNT_LIMIT) {count_threshold_cv.signal(); }
		count_threshold_cv.leave_critical_section();
	}
}
void watch_count(){
	count_threshold_cv.enter_critical_section();
	if (count<COUNT_LIMIT) {
		count_threshold_cv.wait();
		count += 125;
	}

	count_threshold_cv.leave_critical_section();
}
