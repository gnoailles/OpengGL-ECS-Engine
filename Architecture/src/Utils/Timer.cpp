#include <Utils/Timer.h>
#include <ctime>
#include <chrono>
#include <chrono>

using namespace Utils;

Timer::clock::time_point Timer::currentTime = clock::now();

long Timer::frameCount = 0;

Timer::FrameTime Timer::fixedDeltaTime(1/60.f);
Timer::FrameTime Timer::maxDeltaTime(1/60.f);

Timer::FrameTime Timer::elapsedTime(0.f);
Timer::FrameTime Timer::deltaTime(0.f);
Timer::FrameTime Timer::accumulator(0.f);

Timer::Timer()
{
}


Timer::~Timer()
{
}

void Timer::PreUpdate()
{
	frameCount++;
	const auto newTime = clock::now();
	deltaTime = newTime - currentTime;
	if (deltaTime > maxDeltaTime)
		deltaTime = maxDeltaTime;

	currentTime = newTime;
	accumulator += deltaTime;
}

void Timer::FixedUpdate()
{
	elapsedTime += fixedDeltaTime;
	accumulator -= fixedDeltaTime;
}
