#ifndef STAT_INCLUDED
#define STAT_INCLUDED
#include <SDL/SDL.h>
#include "Window.h"
#include "Game.h"
#include "SubMenu.h"
#include "InputManager.h"
#include "GazeObject.h"
#include <spdlog/spdlog.h>

namespace core {

	/// The statistics submenu
	class Statistics : public SubMenu
	{
	public:
		/// Build the statistics menu
		Statistics(Window* window, MusicManager* musicManager, CursorMovementManager* cmm, Config* config);
		~Statistics();

		/// Display the statistics menu
		void display(Game* game) override;

	private:
		/// The translation in common language of the stored statistics
		static std::map<std::string, std::string> translation;

		/// The initialization function of the translation
		static std::map<std::string, std::string> initTranslation();

		/// Return the translation of the given key
		/// If no translation is found, return the key
		std::string getTranslation(std::string key);
	};
}

#endif


