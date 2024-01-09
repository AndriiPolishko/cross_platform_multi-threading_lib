#include <iostream>
#include "my_thread.h"
#include <thread>
void getPower(int a, int& res)
{
	std::cout << a <<" to the power of 2 = " << a * a << std::endl;
	res = a*a;
}

int main()
{
	int res = 0;
	MyThread firstThread(getPower, 2, res);
	firstThread.join();
	std::cout << "Res: " << res;
	return 0;
}