#ifndef CURSOR_MOVEMENT_MANAGER_INCLUDED
#define CURSOR_MOVEMENT_MANAGER_INCLUDED

#include <vector>
#include "Cursor.h"
#include "coord.h"
#include <spdlog/logger.h>

class Config;

namespace  core {
	class Window;

	/// This class manage a set of Cursors and provided a valid cursor position at each call of get_cursor_position
	/// Each cursors are built inside the constructor
	class CursorMovementManager
	{
	public:

		/// Build the cursor movement manager with a default set of cursor (Mouse and Tobii Cursor)
		CursorMovementManager(Window* window, Config* config);
		~CursorMovementManager();

		/// Get the position of the cursor
		/// The function only take the valid cursor position and return the highest priority value
		coord get_cursor_position();

		/// Add a cursor to the set of cursors
		void register_new_cursor(Cursor* cursor);

	private:
		/// The cursors to check
		std::vector<Cursor*> cursors_;

		// The logger
		std::shared_ptr<spdlog::logger> logger_;
	};
}

#endif // CURSOR_MOVEMENT_MANAGER_INCLUDED
