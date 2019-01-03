#include "TimeCounter.h"
#include <SDL/SDL.h>

core::TimeCounter::TimeCounter(unsigned int activationTime) :
startTime_(SDL_GetTicks()),
activationTime_(activationTime)
{
}

bool core::TimeCounter::isTimePassed()
{
	auto ticks = SDL_GetTicks();

	if(ticks - startTime_ >= activationTime_)
	{
		return true;
	}

	return false;
}

void core::TimeCounter::reset()
{
	auto ticks = SDL_GetTicks();

	startTime_ = ticks;
}

unsigned int core::TimeCounter::getRemainingTime()
{
	auto ticks = SDL_GetTicks();

	return activationTime_ - (ticks - startTime_);
}
