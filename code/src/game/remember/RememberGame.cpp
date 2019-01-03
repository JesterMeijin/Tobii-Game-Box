#include "RememberGame.h"
#include "../../Button.h"
#include "../../Utils.h"
#include "../../InputManager.h"
#include "../../Constants.h"
#include "../../GazeObject.h"

game::rg::RememberGame::RememberGame(core::Window* window, core::CursorMovementManager* cmm, std::string name, Config* config, core::MusicManager* musicManager) :
Game(window, cmm, name, config, musicManager),
noNumberedCircles_(window, config, { 100, 150, 100, 100 }),
numberedCircles_(window, config, { 100, 150, 100, 100 }),
frameCounter_(config->get_int("game_remember_frame_rate", -1)),
previousWindowSize_({ window_->get_width(), window_->get_height() }),
levelNb(1),
currentIndex(-1),
haveFailed(false),
gameState(PRE_GAME)
{
	for (int i = 0; i < 9; i++)
	{
		SDL_Rect cropRect = {(i % 3) * 250, (i / 3) * 250, 250, 250};

		auto noNumberedCircle = new rb::Case(i, window_, musicManager, 0, 0, config->get_int("game_remember_case_trigger_time", 1000));

		auto numberedCircle = new core::GameObject(window_, "ressources/games/remember/NumberSprites.png", {0, 0, 100, 100 });
		numberedCircle->setCropRect(cropRect);

		numberedCircles_.add(numberedCircle);
		noNumberedCircles_.add(noNumberedCircle);
	}

	winSound = musicManager->loadSFX("ressources/games/remember/winSound.wav");
	loseSound = musicManager->loadSFX("ressources/games/remember/loseSound.mp3");
}

game::rg::RememberGame::~RememberGame()
{
}

void game::rg::RememberGame::updateNoNumberedCircles(core::coord cursorPos)
{
	noNumberedCircles_.update(cursorPos);
}

void game::rg::RememberGame::updateNumberedCircles(core::coord cursorPos)
{
	numberedCircles_.update(cursorPos);
}

void game::rg::RememberGame::play()
{
	logger_->info("Play game {}", getName());

	core::fx::Button preGameSkip(window_, musicManager, config_->get_int("button_trigger_default", 1000), "Passer >", 36, WHITE_COLOR, "ressources/buttonBackground.png", { 320, 100, 180, 70 });
	core::fx::Button continueButton(window_, musicManager, config_->get_int("button_trigger_default", 1000), "Continuer", 36, WHITE_COLOR, "ressources/buttonBackground.png", { 320, 100, 200, 70 });

	core::TimeCounter startGameCounter(config_->get_int("game_remember_remember_timer", 10 * 2000));

	core::fx::Label pageTitle(window_, "Description", 64, { 20,20 }, { 0x29,0xb6,0xf6,0xFF });
	core::fx::Label levelLabel(window_, "Niveau", 64, { 20,20 }, { 0x29,0xb6,0xf6,0xFF });
	core::fx::Label timeCounterLabel(window_, "", 64, { 20,window_->get_height() - 100 }, { 0x29,0xb6,0xf6,0xFF });
	core::fx::Label endGameLabel(window_, "", 128, { window_->get_width()/3,window_->get_height() / 3 }, { 0x29,0xb6,0xf6,0xFF });
	core::fx::Label gameName(window_, name_, 64, { 370,20 }, { 0x21,0x21,0x21,0xFF });
	core::fx::Label levelNumberLabel(window_, "1", 64, { 240,20 }, { 0x21,0x21,0x21,0xFF });
	core::fx::Label descriptionLabel(window_, core::utils::readText("ressources/games/remember/description.txt"), 24, { 20,150 }, { 0x21,0x21,0x21,0xFF });
	core::fx::Button quitGame(window_, musicManager, config_->get_int("button_trigger_default", 1000), "X", 36, WHITE_COLOR, "ressources/buttonBackground.png", { 100,100, 65, 65});
	core::InputManager* inputManager = core::InputManager::getInstance();
	core::coord cursorPos;
	core::GazeObject gaze_object(window_);

	gameState = PRE_GAME;
	haveFailed = false;

	statisticsManager->load();

	statisticsManager->increment("number_of_games", 1);

	do
	{
		cursorPos = cmm_->get_cursor_position();

		quitGame.update(cursorPos);

		bool quit = inputManager->quitRequested() || quitGame.isButtonPressed();

		if(quit)
		{
			logger_->info("Quit game {}", getName());
			break;
		}

		switch(gameState)
		{
		case WIN_GAME:
			continueButton.update(cursorPos);
			if (continueButton.isButtonPressed())
				gameState = INIT_GAME; 

			endGameLabel.setContent("Victoire !", { 0x29,0xb6,0xf6,0xFF });
			endGameLabel.update(cursorPos, { 0,0,0,0 }, noNumberedCircles_.getResizeRatio());
			break;
		case LOSE_GAME:
			continueButton.update(cursorPos);
			if (continueButton.isButtonPressed())
				gameState = INIT_GAME;

			endGameLabel.setContent("Défaite", { 0xE5,0x39,0x35,0xFF });
			endGameLabel.update(cursorPos);
			break;
		case PRE_GAME:
			leveling = 0;
			descriptionLabel.update(cursorPos);
			pageTitle.update(cursorPos);
			gameName.update(cursorPos);
			preGameSkip.update(cursorPos);

			// display the game description only if it's needed
			if (preGameSkip.isButtonPressed()) {
				gameState = INIT_GAME;
			}

			break;
		case INIT_GAME:
			// reset current game
			//initCases
			logger_->info("{} level {} : Initialize new game", getName(), levelNb);
			initCases();
			currentIndex = -1;
			haveFailed = false;
			gameState = START_GAME;
			levelNumberLabel.setText(std::to_string(levelNb));
			startGameCounter.reset();

			break;
		case START_GAME:
			// ask the user to watch a certain space

			// display the circles with the numbers
			levelLabel.update(cursorPos);
			levelNumberLabel.update(cursorPos);
			updateNumberedCircles(cursorPos);
			timeCounterLabel.setText(std::to_string(startGameCounter.getRemainingTime()/1000));
			timeCounterLabel.update(cursorPos, { 0,0,0,0 }, noNumberedCircles_.getResizeRatio());

			if (startGameCounter.isTimePassed()) {
				startGameCounter.reset();
				gameState = PLAY_GAME;
				logger_->info("{} level {} : Visible phase passed", getName(), levelNb);
			}

			break;
		case PLAY_GAME:

			checkGameState();
			levelLabel.update(cursorPos);
			levelNumberLabel.update(cursorPos);
			updateNoNumberedCircles(cursorPos);

			break;
		}

		//Update gaze position
		gaze_object.update(cursorPos);

		// update the window when all the texture are displayed
		window_->update();

	} while (true);

    statisticsManager->flush();
}

void game::rg::RememberGame::initCases()
{	
	switch (levelNb)
	{
	case 1: 
		leveling = 3;
		break;
	case 3:
		leveling = 4;
		break;
	case 5:
		leveling = 5;
		break;
	case 10:
		leveling = 6;
		break;
	case 15:
		leveling = 7;
		break;
	case 20:
		leveling = 8;
		break;
	case 30:
		leveling = 9;
		break;
	default:
		break;
	}

	for (int i = 0; i < 9; i++) {
		numberedCircles_.getObjects()[i]->setVisible(false);
		noNumberedCircles_.getObjects()[i]->setVisible(false);
	}

	
	// init all the numberedCircles_
	for (int i = 0; i < leveling; i++)
	{
		bool ok = false;

		while (!ok) {

			ok = true;
			
			int x = core::utils::randomInt(numberedCircles_.getProperties().x, numberedCircles_.getProperties().w);
			int y = core::utils::randomInt(numberedCircles_.getProperties().y, numberedCircles_.getProperties().h);

			// check position validity
			for(int j = 0; j < i && ok; j++)
			{
				auto rect = numberedCircles_.getObjects()[j]->getImageRect();

				if(core::utils::isInside(x, y, rect) || core::utils::isInside(x + rect.w, y + rect.h, rect))
				{
					ok = false;
				}
			}

			if(!ok)
			{
				continue;
			}

			auto caseNumber = numberedCircles_.getObjects()[i];
			auto caseNoNumber = noNumberedCircles_.getObjects()[i];

			caseNumber->setImageRect({ x, y, 100, 100 });
			caseNumber->setVisible(true);
			caseNoNumber->setImageRect({ x, y, 100, 100 });
			caseNoNumber->setVisible(true);

		}
	}
}

void game::rg::RememberGame::checkGameState()
{
	for (int i = 0; i < leveling; i++)
	{
		if (noNumberedCircles_.getObjects()[i]->isButtonPressed())
		{
			if(noNumberedCircles_.getObjects()[i]->getIndex() != currentIndex+1)
			{
				haveFailed = true;
				break;
			}
			noNumberedCircles_.getObjects()[i]->setVisible(false);
			currentIndex++;

            statisticsManager->increment("cases_pushed", 1);
		}
	}

	// user finished the game
	if (currentIndex == leveling - 1)
	{
		musicManager->playSFX(winSound);
		gameState = WIN_GAME;
		levelNb++;

		statisticsManager->increment("level_win", 1);
        statisticsManager->setMaxOf("max_level", levelNb);

        logger_->info("{} : User have finish this level, new level = {}", getName(), levelNb);
	}
	else if(haveFailed)
	{
        statisticsManager->increment("level_loose", 1);

		musicManager->playSFX(loseSound);

		gameState = LOSE_GAME;

		logger_->info("{} level {} : User have failed", getName(), levelNb);
	}
}
