#include <pthread.h>
#include <stdio.h>
#include "./include/my_thread.h"

void print_stuff(int a)
{
    const char *message1 = "Dude these treads be bussin` fo real";
    const char *message2 = "straight facts boi";
    printf("%s %i \n", message1, a);
    printf("%s \n", message2);
    pthread_exit(nullptr);
}

int main()
{
    int a = 12;
    MyThread first_thread{print_stuff, a};
    first_thread.join();
    return 0;
}

