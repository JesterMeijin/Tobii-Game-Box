#include "SubMenu.h"
#include "Constants.h"
#include "Utils.h"


core::SubMenu::SubMenu(Window* window, MusicManager* musicManager, CursorMovementManager* cmm, Config* config, std::string title) :
	window_(window),
	musicManager_(musicManager),
	cmm_(cmm),
	config_(config),
	gaze_object(window_),
	pageTitle(window, title, 64, { 20,20 }, { 0x29,0xb6,0xf6,0xFF }),
	ExitButton(window_, musicManager, config_->get_int("button_trigger_default", 1000), "X", 36, WHITE_COLOR, "ressources/buttonBackground.png", { 100,100, 65, 65 })
{
	logger_ = spdlog::get("root");
	inputManager = core::InputManager::getInstance();
}

core::SubMenu::~SubMenu()
{
}

void core::SubMenu::display(Game * game)
{
}