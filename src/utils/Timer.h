#pragma once

#define WINDOWS_TIMER 0

#if WINDOWS_TIMER
#include <Windows.h>
#else
#include <chrono>
#endif

namespace utils
{
#if WINDOWS_TIMER
	class Timer
	{
	private:
		LARGE_INTEGER _start;
		double _frequency;

	public:
		Timer()
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			_frequency = 1.0 / frequency.QuadPart;
			QueryPerformanceCounter(&_start);
		}

		void reset()
		{
			QueryPerformanceCounter(&_start);
		}

		float elapsed()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - _start.QuadPart;
			return (float)(cycles * _frequency);
		}
	};
#else
	class Timer
	{
	private:
		typedef std::chrono::high_resolution_clock HighResolutionClock;
		typedef std::chrono::duration<float, std::milli> milliseconds_type;
		std::chrono::time_point<HighResolutionClock> _start;
	public:
		Timer()
		{
			reset();
		}

		void reset()
		{
			_start = HighResolutionClock::now();
		}

		float elapsed()
		{
			return std::chrono::duration_cast<milliseconds_type>(HighResolutionClock::now() - _start).count() / 1000.0f;
		}

	};
#endif
}