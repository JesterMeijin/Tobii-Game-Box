#include "Button.h"
#include "Constants.h"

core::fx::Button::~Button()
{
	musicManager->freeSFX(pressedSound);
}

core::fx::Button::Button(Window * window, MusicManager* musicManager, int timeCounter, std::string text, int fontSize, SDL_Color color, std::string image_source, SDL_Rect image_xywh, void* payload) :
Button(window, musicManager, timeCounter, text, fontSize, color, image_source, "", image_xywh, true, payload)
{}

core::fx::Button::Button(Window * window, MusicManager* musicManager, int timeCounter, std::string text, int fontSize, SDL_Color color, std::string image_source, SDL_Rect image_xywh, bool setVisible, void* payload) :
Button(window, musicManager, timeCounter, text, fontSize, color, image_source, "", image_xywh, setVisible, payload)
{}

core::fx::Button::Button(Window* window, MusicManager* musicManager, int timeCounter, std::string text, int fontSize, SDL_Color color, std::string image_source, std::string selector, SDL_Rect image_xywh, void* payload):
Button(window, musicManager, timeCounter, text, fontSize, color, image_source, selector, image_xywh, true, payload)
{}

core::fx::Button::Button(Window * window, MusicManager* musicManager, int timeCounter, std::string text, int fontSize, SDL_Color color, std::string image_source, std::string selector, SDL_Rect image_xywh, bool setVisible, void* payload) :
GameObject(window, setVisible, image_source, selector, image_xywh),
text_(text),
time_counter_(timeCounter),
button_label_(window, text, fontSize, {image_xywh.x,image_xywh.y}, color),
button_pressed_(false),
is_active_(true),
payload_(payload),
musicManager(musicManager)
{
	// If no texture has been specified, this is important to change the rect to match the label
	if(texture_ == nullptr)
	{
		image_rect_ = button_label_.getImageRect();
	}

	pressedSound = musicManager->loadSFX("ressources/sound/buttonPressed.mp3");
}

void core::fx::Button::update(coord cursorPosition)
{
	if(!isVisible)
		return;

	SDL_Rect image_rect_resize = { window_->get_width() - image_rect_.x, window_->get_height() - image_rect_.y, image_rect_.w, image_rect_.h};
	SDL_Rect label_rect_resize = { window_->get_width() - image_rect_.x + 20, window_->get_height() - image_rect_.y + 10, button_label_.getImageRect().w, button_label_.getImageRect().h };
	
	window_->updateTexturePosition(texture_, cropRect_, &image_rect_resize);
	button_label_.setImageRect(label_rect_resize);
	button_label_.update(cursorPosition);

	if(!is_active_)
		return;

	if (cursorPosition.x > image_rect_resize.x && cursorPosition.x < image_rect_resize.x + image_rect_resize.w &&
		cursorPosition.y > image_rect_resize.y && cursorPosition.y < image_rect_resize.y + image_rect_resize.h) {
		if (time_counter_.isTimePassed()) {
			time_counter_.reset();
			logger_->debug("Button {} pressed ", text_);
			button_pressed_ = true;
		}
	}
	else {
		time_counter_.reset();
	}
}

void core::fx::Button::update(coord cursorPosition, SDL_Rect frame, ratio resizeRatio)
{
	if (!isVisible)
		return;

	double imageResizeRatio = 1;

	if (resizeRatio.x != 1)
		imageResizeRatio = resizeRatio.x;
	if (resizeRatio.y != 1)
		imageResizeRatio = resizeRatio.y;
	if (resizeRatio.x != 1 && resizeRatio.y != 1)
		imageResizeRatio = (resizeRatio.x + resizeRatio.y) / 2;

	image_rect_ = { (int)((double)image_rect_.x * resizeRatio.x), (int)((double)image_rect_.y * resizeRatio.y), (int)((double)image_rect_.w * imageResizeRatio),  (int)((double)image_rect_.h * imageResizeRatio) };

	window_->updateTexturePosition(texture_, cropRect_, &image_rect_);

	if (!is_active_)
		return;

	if (cursorPosition.x > image_rect_.x && cursorPosition.x < image_rect_.x + image_rect_.w &&
		cursorPosition.y > image_rect_.y && cursorPosition.y < image_rect_.y + image_rect_.h) {
		if (time_counter_.isTimePassed()) {
			time_counter_.reset();
			logger_->debug("Button {} pressed ", text_);
			button_pressed_ = true;
		}
	}
	else {
		time_counter_.reset();
	}
}

void core::fx::Button::gameButtonUpdate(coord cursorPosition, int size, int i)
{
	SDL_Rect gamesButtonArea = { 50,120,window_->get_width() - 400, window_->get_height() - 160 };
	SDL_Rect image_rect_resize = { gamesButtonArea.x + gamesButtonArea.w - i * (gamesButtonArea.w / size) + 5,gamesButtonArea.y,gamesButtonArea.w / size,gamesButtonArea.h };
	SDL_Rect label_rect_resize = { gamesButtonArea.x + (int)((double)gamesButtonArea.w * 1.1) - i * (gamesButtonArea.w / size),gamesButtonArea.y + (int)((double)gamesButtonArea.h * 0.1),button_label_.getImageRect().w, button_label_.getImageRect().h };
	window_->updateTexturePosition(texture_, &image_rect_resize);
	window_->updateTexturePosition(selector_, &image_rect_resize);
	button_label_.setImageRect(label_rect_resize);
	button_label_.update(cursorPosition);

	if (cursorPosition.x > image_rect_resize.x && cursorPosition.x < image_rect_resize.x + image_rect_resize.w &&
		cursorPosition.y > image_rect_resize.y && cursorPosition.y < image_rect_resize.y + image_rect_resize.h) {
		if (time_counter_.isTimePassed()) {
			time_counter_.reset();
			logger_->debug("Button {} pressed ", text_);
			button_pressed_ = true;
		}
	}
	else {
		time_counter_.reset();
	}
}

bool core::fx::Button::isButtonPressed()
{
	if(!is_active_)
	{
		return false;
	}

	bool result = button_pressed_;

	if(result) {
		musicManager->playSFX(pressedSound);
	}

	// reset the button
	button_pressed_ = false;

	return result;
}

void* core::fx::Button::getPayload()
{
	return payload_; 
}

void core::fx::Button::setActive(bool active)
{
	is_active_ = active;
}

void core::fx::Button::setSound(std::string path) {

	musicManager->freeSFX(pressedSound);
	pressedSound = musicManager->loadSFX(path);
}
