#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <spdlog/logger.h>

#include "Window.h"
#include "CursorMovementManager.h"
#include "FrameCounter.h"
#include "StatisticsManager.h"
#include "MusicManager.h"

namespace  core {

    /// This interface is used to represent a Game
    /// Each game have a name and can be played by calling the play function
	class Game
	{
	public:
	    /// This build a game with all the required components to initialize and play a full game
		Game(Window* window, CursorMovementManager* cmm,std::string name, Config* config, MusicManager* musicManager);
		virtual ~Game();

		/// Get the game name
		std::string getName();

		/// Play the game
		/// When you call this function, the game is in standalone mode. It check it status and everything by it's own
		/// When this function return, it mean that the user want to return to the menu
		virtual void play() = 0;

	protected:
	    /// The game name
		std::string name_;

	    /// The window to display objects on the screen
		Window* window_;

		/// The cursor manager to check the position of the cursors
		CursorMovementManager* cmm_;

		/// The configuration of the programm
		Config* config_;

		/// Statistics manager for the game
		StatisticsManager* statisticsManager;

		// The music manager for he game
		MusicManager* musicManager;

		/// The logger
		std::shared_ptr<spdlog::logger> logger_;
	};
}

#endif // GAME_INCLUDED
