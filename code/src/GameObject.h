#ifndef GAME_OBJECT_INCLUDED
#define GAME_OBJECT_INCLUDED

#include "Window.h"
#include "ratio.h"
#include "UncopyableObject.h"

namespace core {

	/// This is used to simplify the program by storing data about a single object in the game
	/// A game object can be anything (from label to button by just displaying something on the screen)
	class GameObject : public UncopyableObject
	{
	public:
		/// Build a game object by settings data by default
		GameObject(Window* window);

		/// Build a game object and specified the image to display
		GameObject(Window* window, std::string image_source, SDL_Rect image_size, SDL_Rect* cropRect = nullptr);

		/// Build a game object and specified the image to display and the selector
		GameObject(Window* window, std::string image_source, std::string selector, SDL_Rect image_size, SDL_Rect* cropRect = nullptr);

		/// Build a game object and specified the image to display, the selector and if the object should be visible by default
		GameObject(Window* window, bool setVisible, std::string image_source, std::string selector, SDL_Rect image_size, SDL_Rect* cropRect = nullptr);

		/// Free the resources used by the object
		virtual ~GameObject();

		/// Update the state of the object
		/// The default implementation only display the image at the given position
		virtual void update(coord cursor_position);

		/// Update the state of the object and resize the image if the window has been changed
		virtual void update(coord cursor_position, SDL_Rect frame, ratio resizeDifference);

		SDL_Rect getImageRect() { return image_rect_; }
		void setImageRect(SDL_Rect new_rect) { image_rect_ = new_rect; }
		void updateSelector(std::string selector);
		void setCropRect(SDL_Rect rect) { cropRect_ = new SDL_Rect(rect); }

		/// Show or hide the object
		void setVisible(bool visible) { isVisible = visible; }


	protected:

		/// The window to display the object on
		Window* window_;

		/// The position of the object on the screen
		SDL_Rect image_rect_;

		/// The crop dimension
		/// This is used to only display a part of the source image on the screen (for example, only the left bottom side)
		SDL_Rect* cropRect_;

		/// The image to display on the screen at each frame
		SDL_Texture* texture_;

		/// The selector for the object
		/// A selector is a texture to display around the object to make it look like it's selected
		SDL_Texture* selector_;

		/// The logger
		std::shared_ptr<spdlog::logger> logger_;

		/// The visible value
		bool isVisible;
	};
}

#endif
