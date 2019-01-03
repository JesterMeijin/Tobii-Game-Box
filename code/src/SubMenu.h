#ifndef SUBMENU_INCLUDED
#define SUBMENU_INCLUDED

#include <SDL/SDL.h>
#include "Window.h"
#include "Label.h"
#include "Button.h"
#include "Game.h"
#include "GazeObject.h"
#include "InputManager.h"
#include <spdlog/spdlog.h>

namespace core {

	/// This class represent a sub menu of the main menu
	/// You can see implementation in Statistics, Leaderboard and Settings
	class SubMenu
	{
	public:
		/// Build a sub menu with all the given values
		SubMenu(Window* window, MusicManager* musicManager, CursorMovementManager* cmm, Config* config, std::string title);
		virtual ~SubMenu();

		/// Display this submenu
		virtual void display(Game* game);

	protected:
		/// The window to display the menu in
		Window* window_;

		/// The configuration of the program
		Config* config_;

		/// The music manager
		MusicManager * musicManager_;

		/// The game selected
		Game* game_;

		/// The cursor manager
		CursorMovementManager* cmm_;

		/// the gaze object
		GazeObject gaze_object;

		/// The input manager
		InputManager* inputManager;

		/// The logger
		std::shared_ptr<spdlog::logger> logger_;

		/// The current cursor position
		coord cursorPosition;

		/// The sub menu page title
		fx::Label pageTitle;

		/// The exit button to return to the main menu
		fx::Button ExitButton;

	};
}

#endif //SUBMENU_INCLUDED