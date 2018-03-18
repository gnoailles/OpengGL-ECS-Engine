#pragma once
#include <string>
#include <chrono>
#include <chrono>

namespace Utils
{
	class Timer
	{
	public:

		using clock = std::chrono::high_resolution_clock;
		using ms = std::chrono::duration<double, std::milli>;
		using sec = std::chrono::duration<double>;

		using FrameTime = sec;


		static long frameCount;

		static FrameTime fixedDeltaTime;
		static FrameTime maxDeltaTime;

		static clock::time_point currentTime;
		static FrameTime elapsedTime;
		static FrameTime deltaTime;
		static FrameTime accumulator;

		Timer();
		~Timer();
		static void PreUpdate();
		static void FixedUpdate();
	};
}
