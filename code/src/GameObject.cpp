#include "GameObject.h"
#include <spdlog/spdlog.h>

core::GameObject::~GameObject()
{
	if (texture_ != nullptr)
	{
		SDL_DestroyTexture(texture_);
	}
}

core::GameObject::GameObject(Window* window) :
	UncopyableObject(),
	window_(window),
	texture_(nullptr),
	selector_(nullptr),
	isVisible(true)
{
	logger_ = spdlog::get("root");
}

core::GameObject::GameObject(Window* window, std::string image_source, SDL_Rect image_size, SDL_Rect* cropRect) :
GameObject(window)
{
	image_rect_ = image_size;
	cropRect_ = cropRect;
	if (!image_source.empty())
	{
		texture_ = window_->loadImage(image_source);
		if (texture_ == nullptr)
		{
			logger_->warn("Unable to initialize texture for game object source = {}", image_source);
		}
	}
}

core::GameObject::GameObject(Window* window, std::string image_source, std::string selector, SDL_Rect image_size, SDL_Rect* cropRect) :
GameObject(window, image_source, image_size, cropRect)
{
	image_rect_ = image_size;
	if (!selector.empty())
	{
		selector_ = window_->loadImage(selector);
		if (selector_ == nullptr)
		{
			logger_->warn("Unable to initialize texture for game object source = {}", selector);
		}
	}
}

core::GameObject::GameObject(Window* window, bool setVisible, std::string image_source, std::string selector, SDL_Rect image_size, SDL_Rect* cropRect):
GameObject(window, image_source, selector, image_size, cropRect)
{
	isVisible = setVisible;
}

void core::GameObject::update(coord cursor_position)
{
	window_->updateTexturePosition(texture_, cropRect_, &image_rect_);
	window_->updateTexturePosition(selector_, &image_rect_);
}

void core::GameObject::update(coord cursor_position, SDL_Rect frame, ratio resizeRatio)

{
	if (!isVisible)
		return;

	double imageResizeRatio = 1;
	
	if (resizeRatio.x != 1)
		imageResizeRatio = resizeRatio.x;
	if (resizeRatio.y != 1)
		imageResizeRatio = resizeRatio.y;
	if (resizeRatio.x != 1 && resizeRatio.y != 1)
		imageResizeRatio = (resizeRatio.x + resizeRatio.y)/2;

	image_rect_ = { (int)((double)image_rect_.x * resizeRatio.x), (int)((double)image_rect_.y * resizeRatio.y), (int)((double)image_rect_.w * imageResizeRatio),  (int)((double)image_rect_.h * imageResizeRatio) };

	window_->updateTexturePosition(texture_, cropRect_, &image_rect_);
}

void core::GameObject::updateSelector(std::string selector)
{
	SDL_DestroyTexture(selector_);

	if (!selector.empty())
	{
		selector_ = window_->loadImage(selector);
		if (selector_ == nullptr)
		{
			logger_->warn("Unable to initialize texture for game object source = {}", selector);
		}
	}
}
