#pragma once
#include <chrono>

#define TIMING 1

#if TIMING
#define TIMER(name) Timer name
#define STOP_LOG(name) { name.Stop(false); std::cout << #name << " took: "; name.Log(); }
#define TIME_SCOPE(name) ScopedTimer name(#name)
#else
#define TIMER(name)
#define STOP_LOG(name)
#define TIME_SCOPE(name)
#endif

class Timer
{
public:
	using Clock = std::chrono::steady_clock;
	using TimePoint = Clock::time_point;
	using Duration = Clock::duration;

	Timer(bool start = true)
		: duration(0)
	{
		if (start) Start();
	}

	void Start()
	{
		start = Clock::now();
	}
	void Stop(bool log = true)
	{
		TimePoint end = Clock::now();
		duration += (end - start);

		if (log) Log();
	}

	void Log()
	{
		using namespace std::chrono;

		uint64_t count = duration.count();
		double millis = (double)count / countPerSec * 1000.0;

		if (millis < 1.0) std::cout << millis * 1000 << "us\n";
		else std::cout << millis << "ms\n";
	}
	Duration GetDuration() { return duration; }
	double GetMillis() { return (double)duration.count() / countPerSec * 1000.0; }

protected:
	static constexpr uint64_t countPerSec = std::chrono::duration_cast<Duration>(std::chrono::seconds{1}).count();

	TimePoint start;
	Duration duration;
};

class ScopedTimer : Timer
{
public:
	ScopedTimer(const char* name_) : Timer(false), name(name_) { Start(); }
	~ScopedTimer() { Stop(false); std::cout << name << " took: "; Log(); }

protected:
	const char* name;
};