#include <iostream>
#include <format>

#include "Timer.h"

uint64_t Fib(uint64_t n)
{
	if (n < 2) return n;
	return Fib(n - 1) + Fib(n - 2);
}

int main()
{
	uint64_t num;
	{
		TIMER(t);
		num = Fib(10);
		STOP_LOG(t);
	}

	std::cout << num << '\n';
}