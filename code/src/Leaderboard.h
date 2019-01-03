#ifndef LB_INCLUDED
#define LB_INCLUDED
#include <SDL/SDL.h>
#include "Window.h"
#include "Game.h"
#include "SubMenu.h"
#include "InputManager.h"
#include "GazeObject.h"
#include <spdlog/spdlog.h>

namespace core {

	/// The leaderboard menu
	/// This is no yet implemented
	class Leaderboard : public SubMenu
	{
	public:
		~Leaderboard();
		Leaderboard(Window* window, MusicManager* musicManager, CursorMovementManager* cmm, Config* config);

		/// Display the leaderboard for the given game
		void display(Game* game) override;
	};
}

#endif

