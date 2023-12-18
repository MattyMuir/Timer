#include <iostream>
#include <format>

#define TIMER_NPRINT
#include "Timer2.h"

uint64_t Fib(uint64_t n)
{
	if (n < 2) return n;
	return Fib(n - 1) + Fib(n - 2);
}

int main()
{
	TIMER(t);
	uint64_t num = Fib(25);
	STOP_LOG(t);

	std::cout << num << '\n';
}