#include "Leaderboard.h"
#include "Constants.h"
#include "Utils.h"

core::Leaderboard::Leaderboard(Window* window, MusicManager* musicManager, CursorMovementManager* cmm, Config* config) :
	SubMenu(window, musicManager, cmm, config, "Leaderboard")
{
}


core::Leaderboard::~Leaderboard()
{
}

void core::Leaderboard::display(Game* game)
{
	game_ = game;
	fx::Label gameName(window_, game_->getName(), 64, { 390,20 }, { 0x21,0x21,0x21,0xFF });

	do
	{
		cursorPosition = cmm_->get_cursor_position();

		ExitButton.update(cursorPosition);
		pageTitle.update(cursorPosition);
		gameName.update(cursorPosition);

		if (ExitButton.isButtonPressed() || inputManager->quitRequested())
		{
			logger_->info("Quit Statistics screen");
			break;
		}

		//Update gaze position
		gaze_object.update(cursorPosition);

		// update the window when all the texture are displayed
		window_->update();

	} while (true);
}
