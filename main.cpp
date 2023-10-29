#include <functional>

#include <iostream>
#include "my_thread.h"

void test(std::string data, int smth)
{
	std::cout << data << std::endl << smth;
}


int main()
{
	MyThread first(test, std::string{"abc"}, 13);
	first.join();
    return 0;
}

