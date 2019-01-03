#include "Window.h"

#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include "spdlog/async.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "Utils.h"

core::Window::Window(Config* config) {

	logger_ = spdlog::get("root");

	// Creates Window
	height = config->get_int("window_height", 600);
	width = config->get_int("window_width", 800);

	Uint32 window_flag = SDL_WINDOW_OPENGL;
	if(config->get_bool("window_fullscreen", false))
	{
		window_flag |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	} 
	else
	{
		window_flag |= SDL_WINDOW_RESIZABLE;
	}

	window = SDL_CreateWindow("Tobii GameBox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flag);
	if (window == nullptr)
	{
		logger_->error("Error while initializing the window : {}", SDL_GetError());

		throw std::exception();
	}
	logger_->debug("Window initialized");

	// Creates the renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)//gestion des erreurs
	{
		logger_->error("Error while initializing the renderer : {}", SDL_GetError());

		throw std::exception();
	}
	logger_->debug("Renderer initialized");

	//Renderer parameters
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	logger_->debug("Window finish initialization width {} height {}", width, height);
}

core::Window::~Window() {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

SDL_Texture* core::Window::loadTextureFromSurface(SDL_Surface* surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture)
	{
		logger_->error("Error while loading the texture : {}", SDL_GetError());

		return nullptr;
	}

	return texture;
}

SDL_Texture* core::Window::loadImage(std::string file)
{
	SDL_Surface* image = IMG_Load(file.c_str()); 
	if (!image)
	{
		logger_->error("Error while loading the image : {}", SDL_GetError());

		return nullptr;
	}

	SDL_Texture* texture = loadTextureFromSurface(image);

	SDL_FreeSurface(image);

	return texture;
}

SDL_Texture* core::Window::loadText(std::string text, TTF_Font* font, SDL_Color color)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, width);
	if (!surfaceMessage)
	{
		logger_->error("Error while loading the surface from text : {}", SDL_GetError());

		return nullptr;
	}

	SDL_Texture* texture = loadTextureFromSurface(surfaceMessage);

	SDL_FreeSurface(surfaceMessage);

	return texture;
}

void core::Window::updateTexturePosition(SDL_Texture* texture, SDL_Rect* dstRect)
{
	updateTexturePosition(texture, nullptr, dstRect);
}

void core::Window::updateTexturePosition(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect)
{
	if (texture != nullptr) {
		SDL_RenderCopy(renderer, texture, srcRect, dstRect);
	}
}

void core::Window::update()
{
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}

core::coord core::Window::get_offset_xy()
{
	coord c = {0,0};

	SDL_GetWindowPosition(window, &(c.x), &(c.y));

	return c;
}

core::coord core::Window::get_display_resolution()
{

	SDL_DisplayMode current;

	SDL_GetCurrentDisplayMode(0, &current);
	coord c = { current.w, current.h };

	return c;
}
