#include <spdlog/spdlog.h>

#include "Cursor.h"

core::Cursor::Cursor()
{
	logger_ = spdlog::get("root");
}
