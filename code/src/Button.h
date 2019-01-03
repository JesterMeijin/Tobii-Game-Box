#ifndef BUTTON_INCLUDED
#define BUTTON_INCLUDED

#include "Window.h"
#include "TimeCounter.h"
#include "Label.h"
#include "GameObject.h"
#include "MusicManager.h"

/// The main package of the application
namespace core 
{
	/// The fx package for utility class
	namespace fx
	{
		/// A button for the game
		/// Each button status is check at each call of the update function
		/// The status can be checked via the isButtonPressed function
		class Button : public GameObject
		{
		public:
			/// Construct a Button with all the needed attributes
			Button(Window* window, MusicManager* musicManager, int timeCounter, std::string text, int fontSize, SDL_Color color, std::string image_source, SDL_Rect image_xywh, void* payload = nullptr);

			/// Construct a Button with all the needed attributes and set the visible attributes default value
			Button(Window* window, MusicManager* musicManager, int timeCounter, std::string text, int fontSize, SDL_Color color, std::string image_source, SDL_Rect image_xywh, bool setVisible, void* payload = nullptr);

			/// Construct a Button with all the needed attributes and a selector representing if the button is clicked or not
			Button(Window* window, MusicManager* musicManager, int timeCounter, std::string text, int fontSize, SDL_Color color, std::string image_source, std::string selector, SDL_Rect image_xywh, void* payload = nullptr);

			/// Construct a Button with all the needed attributes and set the visible attributes default value and a selector representing if the button is clicked or not
			Button(Window* window, MusicManager* musicManager, int timeCounter, std::string text, int fontSize, SDL_Color color, std::string image_source, std::string selector, SDL_Rect image_xywh, bool setVisible, void* payload = nullptr);

			/// Free this button
			~Button();

			/// Update the status of this button with the cursorPosition
			/// if cursorPosition is inside the button for a time, it update the status of the button to pressed
			void update(coord cursorPosition) override;

			/// Same as the previous definition but with parameters to auto resize the button
			void update(coord cursor_position, SDL_Rect frame, ratio resizeRatio) override;

			/// Update the button with a special treatment for game buttons inside the menu
			void gameButtonUpdate(coord cursorPosition, int size, int i);

			/// Check if the button has been pressed
			/// When the button has been pressed, it play the pressedSound and reset the value of button_pressed_ to false
			bool isButtonPressed();

			/// In the constructor you can specify a payload for a specific button to know which action to execute
			void* getPayload();

			/// Activate this button or not
			/// The state of a disable button is not checked
			void setActive(bool active);

			/// Set the sound to be played when the button is pressed
			void setSound(std::string path);

		protected:
			/// The text of the button
			std::string text_;

			/// The timecounter representing the trigger time of this button
			TimeCounter time_counter_;

			/// The label inside the button
			Label button_label_;

			/// The value to store if the button has been pressed or not
			bool button_pressed_;

			/// The status of the button (enable, disable)
			bool is_active_;

			/// The payload stored in this button
			void* payload_;

			/// The music manager to play the pressedSound
			MusicManager* musicManager;

			/// The sound to play when it has been pressed
			Mix_Chunk* pressedSound;
		};
	}
}

#endif // BUTTON_INCLUDED
