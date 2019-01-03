#include "Game.h"
#include "Utils.h"
#include <spdlog/spdlog.h>

core::Game::Game(Window* window, CursorMovementManager* cmm, std::string name, Config* config, MusicManager* musicManager) :
name_(name),
window_(window),
config_(config),
statisticsManager(new StatisticsManager(name)),
musicManager(musicManager),
cmm_(cmm)
{
	logger_ = spdlog::get("root");
}

core::Game::~Game()
{
	core::utils::safe_delete(statisticsManager);
}

std::string core::Game::getName()
{
	return name_;
}
