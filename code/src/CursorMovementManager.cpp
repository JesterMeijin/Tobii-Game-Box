#include "CursorMovementManager.h"
#include "MouseCursor.h"
#include "TobiiCursor.h"
#include <spdlog/spdlog.h>
#include <SDL/SDL.h>
#include "Utils.h"

core::CursorMovementManager::CursorMovementManager(Window* window, Config* config)
{
	logger_ = spdlog::get("root");

	try {
		register_new_cursor(new core::MouseCursor());
		logger_->debug("Mouse cursor initialized");
	}
	catch (std::exception& ex) {
		logger_->error("Error initializing cursors : {}", ex.what());
		throw std::exception("Cursors init problem");
	}

	try {
		register_new_cursor(new core::TobiiCursor(window, config));
		logger_->debug("Tobii cursor initialized");
	}
	catch (std::exception& ex) {
		logger_->error("Error initializing cursors : {}", ex.what());
		throw std::exception("Cursors init problem");
	}
}

core::CursorMovementManager::~CursorMovementManager()
{
	for(auto cursor : cursors_)
	{
		utils::safe_delete(cursor);
	}
}

core::coord core::CursorMovementManager::get_cursor_position()
{
	int priority = -1;
	coord value = {0, 0};

	for (auto cursor : cursors_)
	{
		if(cursor->getPriority() > priority)
		{
			coord tmp = { 0,0 };
			const bool valid = cursor->get_cursor_position(tmp);
			if(valid)
			{
				priority = cursor->getPriority();
				value = tmp;
			}
		}
	}

	return value;
}

void core::CursorMovementManager::register_new_cursor(Cursor* cursor)
{
	cursors_.push_back(cursor);
}
