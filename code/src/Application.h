#ifndef APPLICATION_INCLUDED
#define APPLICATION_INCLUDED
#include "Window.h"
#include <memory>
#include <spdlog/logger.h>
#include "CursorMovementManager.h"
#include "InputManager.h"
#include "FrameCounter.h"
#include "Config.h"
#include "Game.h"
#include "Menu.h"

/// The main package of the application
namespace  core {

	/// This class is the main class of the software
	/// It run the main loop of the program inside the run method
	class Application
	{
	public:
		/// This initialize the attributes by default
		Application();

		/// Free all the games and attributes
		~Application();

		/// Main loop of the program
		/// At the beginning this call the init function
		/// This call (among others) the menu update function to display the menu
		void run(int argc, char* argv[]);

	private:

		/// This initialize all the Application components and load the configuration with the execution parameters
		void init(int argc, char* argv[]);

		/// The window to display everything
		Window* window_;

		/// The configuration of the program loaded at the beginning of the init function
		Config* config_;

		/// The main loop frame counter
		FrameCounter* frame_counter_;

		/// The cursor manager to catch the position of the different available cursors
		CursorMovementManager* cursor_movement_manager_;

		// The spd library logger
		std::shared_ptr<spdlog::logger> logger_;

		/// The input manager to catch keyboard events and quit request
		InputManager* inputManager;

		/// The available games of the program.
		/// By adding game in this list you automaticaly add a button to the menu and mae it available to everyone
		std::vector<Game*> games_;

		/// The software menu with the game buttons and others button
		Menu* menu_;

		/// The music manager to play music in background
		MusicManager* musicManager;
	};
}

#endif //APPLICATION_INCLUDED