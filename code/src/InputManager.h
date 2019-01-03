/// InputManager was taken from https://github.com/alexdantas/sdl2-platformer
/// This file is under GNU General Public License (see here https://github.com/alexdantas/sdl2-platformer#license)


#ifndef INPUT_MANAGER_INCLUDED
#define INPUT_MANAGER_INCLUDED

#include <string>
#include <SDL/SDL.h>
#include "InputDefinition.h"


namespace core {

	/// Singleton to manage the keyboard input of the game
	/// This class has been taken from https://github.com/alexdantas/sdl2-platformer repository
	class InputManager
	{
	public:
		/// Returns the singleton instance of this class.
		///
		/// This assures that only a single instance of this class is
		/// created at any point on the game.
		static InputManager* getInstance();

		/// Updates the entire game input state.
		///
		/// @note You should call this at every frame to assure
		///        expected behaviour. Pretty much all things depend
		///        on this.
		///
		/// This method deals with very low-level SDL calls.
		///
		/// But what it _really_ does is check the keyboard/mouse for
		/// any signs at all (keys down, keys up, mouse pressed,
		/// mouse X...) and update internal variables that reflect
		/// that.
		///
		void update(int cameraX = 0, int cameraY = 0);

		/// Tells if the keyboard `key` was released just now.
		bool isKeyDown(int key);

		/// Tells if the keyboard `key` was pressed just now.
		bool isKeyUp(int key);

		/// Helper to tell if any Shift is being hold.
		bool shift();

		/// Helper to tell if any Ctrl is being hold.
		bool ctrl();

		/// Helper to tell if any Alt is being hold.
		bool alt();

		/// Tells if the mouse `button` was released just now.
		bool isMouseDown(MouseButton button);

		/// Tells if the mouse *button* was pressed just now.
		bool isMouseUp(MouseButton button);

		/// Tells if the `key` is currently being pressed.
		bool isKeyPressed(KeyboardKey key);

		/// Tells if the mouse `button` is currently being pressed.
		bool isMousePressed(MouseButton button);

		/// Tells if the user asked the game to quit.
		bool quitRequested();

		/// Returns the current mouse X position.
		int getMouseX();

		/// Returns the current mouse Y position.
		int getMouseY();

		/// Locks the `InputManager`, preventing it to actually
		/// refresh input and making all methods returning `false`
		/// (except for `quitRequested()`.
		///
		/// @note For an explanation and tutorial,
		///       see the header of this class.
		///
		void lock();

		/// Unlocks the `InputManager`, allowing it to respond
		/// normally to input.
		///
		void unlock();

		/// Tells if the mouse's currently inside `rectangle`.
		bool isMouseInside(SDL_Rect rectangle);

		// Those deal with printable keys
		// (keys on the ASCII table that can be shown onscreen - not
		// control-characters)

		/// Tells if the *key* can be printed onscreen
		/// (not a control key).
		/// If a key is visible according to the ASCII table.
		static bool isPrintable(SDL_Keycode key);

		bool isPrintableKeyDown();
		std::string getCurPrintableKey();

		// WUT

		InputManager();

		// Removing copy-constructor and assignment operator.
		InputManager(InputManager const&) {};
		void operator=(InputManager const&) {};
		

	private:
		/// Current single instance of the class.
		static InputManager* instance;

		/// Saves SDL internal keyboard state.
		const uint8_t* keyboard;

		/// Saves SDL internal mouse state.
		uint32_t mouse;

		/// Current mouse X position.
		int mouseX;

		/// Current mouse Y position.
		int mouseY;

		/// Saves which keys are currently down.
		///
		/// @note *KEYBOARD_SIZE* is defined on *SDL.hpp*.
		bool keyDown[KEYBOARD_SIZE];

		/// Saves which keys are currently up.
		///
		/// @note *KEYBOARD_SIZE* is defined on *SDL.hpp*.
		bool keyUp[KEYBOARD_SIZE];

		/// Saves which mouse buttons are currently down.
		///
		/// @note *MOUSE_SIZE* is defined on *SDL.hpp*.
		bool mouseDown[MOUSE_MAX];

		/// Saves which mouse buttons are currently up.
		///
		/// @note *MOUSE_SIZE* is defined on *SDL.hpp*.
		bool mouseUp[MOUSE_MAX];

		/// Tells if we must quit the game.
		bool will_quit;

		/// If the user pressed a printable key, this is where
		/// it'll be stored.
		int curPrintableKey;

		/// Tells if the input manager is currently locked.
		bool isLocked;
	};

}

#endif //INPUT_MANAGER_INCLUDED