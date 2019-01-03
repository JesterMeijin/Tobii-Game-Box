#ifndef MENU_INCLUDED
#define MENU_INCLUDED

#include <SDL/SDL.h>
#include "Window.h"
#include "Label.h"
#include "Button.h"
#include "Game.h"
#include "Statistics.h"
#include "Leaderboard.h"
#include "Settings.h"
#include <spdlog/spdlog.h>

namespace  core {

	/// The Menu of the game
	/// This class is used to not overload the application class
	class Menu 
	{
	public:
		/// Build the menu with all the required parameters and sub menu
		Menu(Window* window, MusicManager* musicManager, std::vector<Game*>& games, Statistics* statistics, Leaderboard* leaderboard, Settings* settings);
		~Menu();

		/// Update the menu
		bool update(coord cursorPosition);

	private:
		/// The window to display the menu in
		Window* window_;

		/// The selected game in the menu
		Game* game;

		/// The statistics submenu
		Statistics* statistics_;

		/// The leaderboard submenu
		Leaderboard* leaderboard_;

		/// The settings submenu
		Settings* settings;

		/// The playable games of the application
		std::vector<fx::Button*> game_buttons_;

		/// The main title labels
		fx::Label main_title_text_Tobii;
		fx::Label main_title_text_GameBox;

		/// The differents buttons of the application
		fx::Button LeaderBoardButton;
		fx::Button StatisticsButton;
		fx::Button SettingsButton;
		fx::Button PlayButton;
		fx::Button ExitButton;

		/// The logger
		std::shared_ptr<spdlog::logger> logger_;
	};
}
#endif //MENU_INCLUDED