#ifndef FRAME_COUNTER_INCLUDED
#define FRAME_COUNTER_INCLUDED
#include <SDL/SDL_hints.h>

namespace core {

	/// This class is used to count the number of frame between each call and delay if it's needed
	class FrameCounter
	{
	public:
		/// Build a frame counter with a given frame rate
		explicit FrameCounter(int fps);
		~FrameCounter() = default;

		/// Delay the next frame if this needed (a frame take a given time and it delay the time that is not passed yet)
		void delay_if_needed();

	private:
		/// The frame per second rate
		unsigned int fps_;

		/// The internal clock of the program
		Uint32 clock_;
	};
}

#endif //FRAME_COUNTER_INCLUDED
