#include "GazeObject.h"

core::GazeObject::GazeObject(Window* window) :
GameObject(window, "ressources/gaze.png", { 0,0,200,200 })
{

}

core::GazeObject::~GazeObject()
{
}

void core::GazeObject::update(coord gazePosition)
{
	image_rect_.x = gazePosition.x - image_rect_.w / 2;
	image_rect_.y = gazePosition.y - image_rect_.h / 2;

	window_->updateTexturePosition(texture_, &image_rect_);
}
