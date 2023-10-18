#include <pthread.h>
#include <cstdio>
#include "./include/my_thread.h"

void print_stuff(int a)
{
    const char *message1 = "Dude these treads be bussin` fo real";
    const char *message2 = "straight facts boi";
    printf("%s %i \n", message1, a);
    printf("%s \n", message2);
    pthread_exit(nullptr);
}

int global_stuff = 0;
MyMutex mutex1;

void iterate_global_stuff1()
{
	mutex1.lock();
	for(int i = 0; i < 10; i++)
	{
		printf("%d\n", global_stuff++);
	}
	mutex1.unlock();
}

int main()
{
    int a = 12;
    MyThread first_thread{iterate_global_stuff1};
    MyThread second_thread{iterate_global_stuff1};
    first_thread.join();
    second_thread.join();
    return 0;
}

