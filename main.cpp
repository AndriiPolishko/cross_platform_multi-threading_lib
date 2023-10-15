#include <pthread.h>
#include <stdio.h>
#include "./include/my_thread.h"

void print_stuff()
{
    const char *message1 = "Dude these treads be bussin` fo real";
    const char *message2 = "straight facts boi";
    printf("%s \n", message1);
    printf("%s \n", message2);
    pthread_exit(nullptr);
}

int main()
{
    MyThread first_thread{print_stuff};
    first_thread.join();
    return 0;
}

