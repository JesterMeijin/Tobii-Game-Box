#ifndef CURSOR_INCLUDED
#define CURSOR_INCLUDED

#include <spdlog/logger.h>

#include "coord.h"

namespace  core {

	/// The cursor interface is built to provide interface to have multiples way to interact with the software
	/// To see implementation see TobiiCursor and MouseCursor
	class Cursor
	{
	public:
		/// Initialize the cursor
		Cursor();
		virtual ~Cursor() = default;

		/// Pur virtual function to implements
		/// This provide the position of the cursor
		/// it modifies directly the given value by reference
		/// It return a boolean to say if the value is valid or not
		virtual bool get_cursor_position(coord& value) = 0;

		/// Pur virtual function to implements
		/// It represent the priority of the cursor
		/// Higher priority mean that the cursor position should be taken instead of another
		virtual int getPriority() = 0;

	protected:

		/// The loggerg
		std::shared_ptr<spdlog::logger> logger_;
	};
}

#endif // CURSOR_INCLUDED