#include "FrameCounter.h"
#include <SDL/SDL.h>

core::FrameCounter::FrameCounter(int fps): 
fps_(0),
clock_(0)
{
	if (fps < 0)
		fps_ = 0;
	else
		fps_ = static_cast<unsigned>(fps);
}

void core::FrameCounter::delay_if_needed()
{
	// get the time 
	if (fps_ != 0 && (1000 / fps_) > SDL_GetTicks() - clock_)
	{
		SDL_Delay(1000 / fps_ - (SDL_GetTicks() - clock_));
	}

	clock_ = SDL_GetTicks();
}

