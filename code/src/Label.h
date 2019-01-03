#ifndef LABEL_INCLUDED
#define LABEL_INCLUDED
#include "Window.h"
#include "GameObject.h"

namespace core
{
	namespace fx
	{
		/// This class represent a text to display on the screen
		/// The tet is loaded with SDL_TTF and stored in the gameobject image
		class Label : public GameObject
		{
		public:
			/// Build a label with the given text, at the given position with the given color and size
			Label(Window* window, std::string text, int fontSize, coord pos, SDL_Color color);
			~Label();
	
			/// Update the label
			void update(coord cursor_position) override;

			/// Same as the previous definition but with parameters to auto adapt the text position
			void update(coord cursor_position, SDL_Rect frame, ratio resizeRatio) override;

			///  Change the text of the label
			void setText(std::string text);

			/// Change the text and the color of the label
			void setContent(std::string text, SDL_Color color_);
		private:
			/// The SDL TTF font
			TTF_Font* font_;

			/// The color of the label
			SDL_Color color_;
		};
	}
}

#endif