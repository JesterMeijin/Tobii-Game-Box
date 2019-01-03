#include "Label.h"

core::fx::Label::Label(Window* window, std::string text, int fontSize, coord pos, SDL_Color color):
GameObject(window),
color_(color)
{
	font_ = TTF_OpenFont("ressources/Roboto.ttf", fontSize);

	image_rect_ = { pos.x,pos.y,0,0 };

	setText(text);	
}

core::fx::Label::~Label()
{
	TTF_CloseFont(font_);
}

void core::fx::Label::update(coord cursor_position)
{
	window_->updateTexturePosition(texture_, &image_rect_);
}

void core::fx::Label::update(coord cursorPosition, SDL_Rect frame, ratio resizeRatio)
{
	SDL_Rect image_rect_resize = { (int)((double)image_rect_.x * resizeRatio.x), (int)((double)image_rect_.y * resizeRatio.y), image_rect_.w, image_rect_.h };

	window_->updateTexturePosition(texture_, &image_rect_resize);
}

void core::fx::Label::setContent(std::string text, SDL_Color color)
{
	if (texture_ != nullptr)
		SDL_DestroyTexture(texture_);

	color_ = color;
	texture_ = window_->loadText(text, font_, color_);
	SDL_QueryTexture(texture_, nullptr, nullptr, &image_rect_.w, &image_rect_.h);
}

void core::fx::Label::setText(std::string text)
{
	if (texture_ != nullptr)
		SDL_DestroyTexture(texture_);

	texture_ = window_->loadText(text, font_, color_);
	SDL_QueryTexture(texture_, nullptr, nullptr, &image_rect_.w, &image_rect_.h);
}
