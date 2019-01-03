#include "Settings.h"
#include "Constants.h"
#include "Utils.h"

core::Settings::Settings(Window *window, MusicManager *musicManager, CursorMovementManager *cmm, Config *config) :
        SubMenu(window, musicManager, cmm, config, "Parametres") {
}


core::Settings::~Settings() {
}

void core::Settings::display(Game *game) 
{

	std::vector<core::fx::Label *> labels;
	labels.push_back(new core::fx::Label(window_, "Musiques & Sons", 36, { 20,150 }, { 0x29, 0xb6, 0xf6, 0xFF }));
	core::fx::Button enableMusicButton(window_, musicManager_, 1000, "Oui", 36, WHITE_COLOR, "ressources/buttonBackground.png", { window_->get_width() - 400, window_->get_height() - 145,150,70 });
	core::fx::Button disableMusicButton(window_, musicManager_, 1000, "Non", 36, WHITE_COLOR, "ressources/buttonBackground.png", { window_->get_width() - 600, window_->get_height() - 145,150,70 });

	if (config_->get_bool("music_default_enable", true)) {
		enableMusicButton.setVisible(false);
		disableMusicButton.setVisible(true);
	}
	else {
		enableMusicButton.setVisible(true);
		disableMusicButton.setVisible(false);
	}


    do {
        cursorPosition = cmm_->get_cursor_position();

        ExitButton.update(cursorPosition);
        pageTitle.update(cursorPosition);

        if (ExitButton.isButtonPressed() || inputManager->quitRequested()) {
            logger_->info("Quit Settings screen");
            break;
        }

		// Update buttons
		enableMusicButton.update(cursorPosition);
		disableMusicButton.update(cursorPosition);
		if (enableMusicButton.isButtonPressed())
		{
			enableMusicButton.setVisible(false);
			disableMusicButton.setVisible(true);
			config_->set_bool("music_default_enable", true);
			musicManager_->enable(true);
			logger_->info("music_default_enable sets to {}", config_->get_bool("music_default_enable", true));
		}
		if (disableMusicButton.isButtonPressed())
		{
			enableMusicButton.setVisible(true);
			disableMusicButton.setVisible(false);
			config_->set_bool("music_default_enable", false);
			musicManager_->enable(false);
			logger_->info("music_default_enable sets to {}", config_->get_bool("music_default_enable", true));
		}

		// Update Labels
		for (auto &label : labels) {
			label->update(cursorPosition);
		}

        //Update gaze position
        gaze_object.update(cursorPosition);

        // update the window when all the texture are displayed
        window_->update();

    } while (true);
}