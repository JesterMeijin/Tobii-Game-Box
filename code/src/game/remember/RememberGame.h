#ifndef REMEMBER_GAME_INCLUDED
#define REMEMBER_GAME_INCLUDED

#include "../../Game.h"
#include "../../ratio.h"
#include "../../coord.h"
#include "../../Frame.h"
#include "Case.h"

/// The game status
enum RememberGameState
{
	WIN_GAME, /// This mean that the user have wined the current level
	LOSE_GAME, /// This mean that the user have loosed the current level
	PRE_GAME, /// This state represent the explication status where the game is explained
	INIT_GAME, /// This represent the initialization of the level according levelNb and leveling
	START_GAME, /// In this state, the game display numberedCircles_
	PLAY_GAME /// In this state, the game display noNumberedCircles_ and check the current status
};

namespace game {

	/// The remember game package
	namespace rg {

		/// The class for the Remember game
		/// This game is about remembering the positions of ordered cases (see Case.h)
		/// You have different game status in this game (see RememberGameState).
		/// As you can see, this class implements the Game interface with the play method in order to be used by the program
		class RememberGame : public core::Game
		{
		public:

			/// Build a game with all the needed classes (Window CursorMovementManager, ...)
			/// The game name is provided by the 'name' argument
			RememberGame(core::Window* window, core::CursorMovementManager* cmm, std::string name, Config* config, core::MusicManager* musicManager);
			~RememberGame();

			/// Implementation of the Game play
			void play() override;

		private:

			/// Init the position of the cases on the screen
			/// This initialize the 'Case's objects and a set of gameObject with a label inside representing the "numbered cases"
			/// Each cases is assigned to a random position and can't be over another
			void initCases();

			/// This update the state and display of the game objects with the case number inside
			/// This is a for loop update on numberedCircles_
			void updateNumberedCircles(core::coord cursorPos);

			/// This update the cases objects state's
			/// This is a for loop update on noNumberedCircles_
			void updateNoNumberedCircles(core::coord cursorPos);

			/// This check if one of the noNumberedCircles_ has been clicked
			/// If one has been, it check if the game is loosed or wined by comparing currentIndex with the case index
			void checkGameState();

			/// The sound to be played when the game is wined
			Mix_Chunk* winSound;
			/// The sound to be played when the game is loosed
			Mix_Chunk* loseSound;

			/// The frame counter of the game
			core::FrameCounter frameCounter_;

			/// The previous size of the window (for resizing purposes)
			core::coord previousWindowSize_;

			/// The cases objects. These are the clickable cases without numbers inside
			core::fx::Frame<game::rb::Case> noNumberedCircles_;
			/// The GameObject representing the cases but with number
			core::fx::Frame<core::GameObject> numberedCircles_;

			/// The current level number
			int levelNb;

			/// The current difficulty index
			int leveling;

			/// The current index of the last cases clicked
			/// The next expected index to be clicked is currentIndex+1
			int currentIndex;

			/// Store if the used have failed the current level
			bool haveFailed;

			/// The current game state
			RememberGameState gameState;
		};
	}
}

#endif // REMEMBER_GAME_INCLUDED