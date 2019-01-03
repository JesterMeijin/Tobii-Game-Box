#include "MouseCursor.h"
#include "InputManager.h"

core::MouseCursor::MouseCursor() : 
Cursor()
{
	
}

core::MouseCursor::~MouseCursor()
{

}

bool core::MouseCursor::get_cursor_position(coord& value)
{
	InputManager* input_manager = InputManager::getInstance();

	input_manager->update();
	
	value = { input_manager->getMouseX(), input_manager->getMouseY() };

	logger_->trace("Mouse cursor position x:{} y:{}", value.x, value.y);

	return true;
}

int core::MouseCursor::getPriority()
{
	return 10;
}
