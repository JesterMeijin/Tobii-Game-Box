#ifndef MOUSE_CURSOR_INCLUDED
#define MOUSE_CURSOR_INCLUDED

#include "Cursor.h"

namespace  core {
	/// This represent a cursor with the mouse position
	class MouseCursor : public Cursor
	{
	public:
		MouseCursor();
		~MouseCursor();

		/// This return the mouse position
		bool get_cursor_position(coord& value) override;

		/// This return a low priority (mouse is not the principal game controller)
		int getPriority() override;

	};
}

#endif // MOUSE_CURSOR_INCLUDED