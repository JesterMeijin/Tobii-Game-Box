#include "Menu.h"
#include "Constants.h"
#include "Utils.h"


core::Menu::Menu(Window* window, MusicManager* musicManager, std::vector<Game*>& games, Statistics* statistics, Leaderboard* leaderboard, Settings* settings):
window_(window),
statistics_(statistics),
leaderboard_(leaderboard),
settings(settings),
main_title_text_Tobii(window, "Tobii", 64, { 20,20 }, { 0x29,0xb6,0xf6,0xFF }),
main_title_text_GameBox(window, "Game Box", 64, { 180,20 }, {0x21,0x21,0x21,0xFF}),
PlayButton(window, musicManager, 1000, "Jouer", 36, WHITE_COLOR, "ressources/buttonBackground.png", { 300,480,250,70 }, false),
LeaderBoardButton(window, musicManager, 1000, "Leaderboard", 36, WHITE_COLOR, "ressources/buttonBackground.png", { 300,390,250,70 }, false),
StatisticsButton(window, musicManager, 1000, "Statistiques", 36, WHITE_COLOR, "ressources/buttonBackground.png", { 300,310,250,70 }, false),
SettingsButton(window, musicManager, 1000, "Parametres", 36, WHITE_COLOR, "ressources/buttonBackground.png", { 300,230,250,70 }),
ExitButton(window, musicManager, 1000, "Quitter", 36, WHITE_COLOR, "ressources/buttonBackground.png", { 300, 150,250,70 })
{
	logger_ = spdlog::get("root");

	for (auto game : games)
	{
		game_buttons_.push_back(new fx::Button(window, musicManager, 1000, game->getName(), 32, { 0x29,0xb6,0xf6,0xFF }, "ressources/games/"+ core::utils::toLowerCase(game->getName())+"/GameImage.png", "ressources/GameButtonBackground.png", { 0,0,0,0}, game));
	}
}

core::Menu::~Menu()
{
	for(auto& gameButton : game_buttons_)
	{
		utils::safe_delete(gameButton);
	}
}

bool core::Menu::update(coord cursorPosition)
{
	int i = 0;

	for (auto& button : game_buttons_)
	{
		i++;
		button->gameButtonUpdate(cursorPosition, (int)game_buttons_.size(), i);


		if(button->isButtonPressed())
		{
			for (auto& gameButton : game_buttons_)
				gameButton->updateSelector("ressources/GameButtonBackground.png");

			button->updateSelector("ressources/SelectedGameButtonBackground.png");
			button->gameButtonUpdate(cursorPosition, (int)game_buttons_.size(), i);
			PlayButton.setVisible(true);
			StatisticsButton.setVisible(true);
			LeaderBoardButton.setVisible(true);

			// Find if the button is attached to a payload (a Game in this case)
			auto payload = button->getPayload();

			if(payload != nullptr)
			{
				// there is a payload
				game = static_cast<Game*>(payload);
			}

		}
	}

	main_title_text_Tobii.update(cursorPosition);
	main_title_text_GameBox.update(cursorPosition);
	LeaderBoardButton.update(cursorPosition);
	if (LeaderBoardButton.isButtonPressed())
		leaderboard_->display(game);
	StatisticsButton.update(cursorPosition);
	if(StatisticsButton.isButtonPressed())
		statistics_->display(game);
	SettingsButton.update(cursorPosition);
	if(SettingsButton.isButtonPressed())
		settings->display(nullptr);
	ExitButton.update(cursorPosition);
	if (ExitButton.isButtonPressed())
		return true;
	PlayButton.update(cursorPosition);
	if (PlayButton.isButtonPressed() && game != nullptr)
		game->play(); // play the game

	return false;
}
