#ifndef WINDOW_INCLUDED
#define WINDOW_INCLUDED
#include <SDL\SDL.h>
#include <SDL\SDL_ttf.h>
#include <spdlog/logger.h>
#include "coord.h"
#include "Config.h"

class Config;

namespace  core {

	/// This file contains the application screen
	/// The class window is used to create the textures from ressources images and display then on the screen
	class Window
	{
	public:
		/// Build the window according to the application configuration
		explicit Window(Config* config);
		~Window();

        /// Load a texture from the given image path
        SDL_Texture* loadImage(std::string file);

        /// Load a text as an image representing the text
        SDL_Texture* loadText(std::string text, TTF_Font* font, SDL_Color color);

        /// Update the texture on the screen
		void updateTexturePosition(SDL_Texture* texture, SDL_Rect* dstRect);

        /// Update the texture on the screen but crop it before
		void updateTexturePosition(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect);

		/// Update the screen
		/// This mean that all the modification on the image buffer are flushed into the OS to be dispayed on the screen
		void update();

		/// Get the window height
		int get_height() { SDL_GetWindowSize(window, &width, &height); return height; }

        /// Get the window width
        int get_width() { SDL_GetWindowSize(window, &width, &height); return width; }

        /// Get the window position in the user monitor
        coord get_offset_xy();

		/// Get the user display resolution
		coord get_display_resolution();

	private:
		/// Load a texture from the give surface (SDL related stuff)
		SDL_Texture* loadTextureFromSurface(SDL_Surface* surface);

        /// The width and height of the application
		int height, width;

		/// The SDL Window
		SDL_Window* window;

		/// The SDL renderer
		SDL_Renderer* renderer;

		/// The logger
		std::shared_ptr<spdlog::logger> logger_;
	};
}

#endif // WINDOW_INCLUDED
