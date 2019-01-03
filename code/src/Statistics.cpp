#include "Statistics.h"
#include "Constants.h"
#include "Utils.h"

std::map<std::string, std::string> core::Statistics::translation = core::Statistics::initTranslation();

core::Statistics::Statistics(Window *window, MusicManager *musicManager, CursorMovementManager *cmm, Config *config) :
        SubMenu(window, musicManager, cmm, config, "Statistiques") {}

core::Statistics::~Statistics() {
}

void core::Statistics::display(Game *game) {
    game_ = game;
    fx::Label gameName(window_, game_->getName(), 64, {370, 20}, {0x21, 0x21, 0x21, 0xFF});

    std::vector<core::fx::Label *> labels;
    SDL_Color firstColor = {0x29, 0xb6, 0xf6, 0xFF};
    SDL_Color secondColor = {0x21, 0x21, 0x21, 0xFF};

    StatisticsManager statisticsManager(game->getName());
    statisticsManager.load();
    auto stats = statisticsManager.getStatistics();

    // Creating labels about stats
    int y = 150;
    for (const auto &entry : stats) {
        core::fx::Label *first = new core::fx::Label(window_, getTranslation(entry.first), 32, {20, y}, firstColor);
        core::fx::Label *second = new core::fx::Label(window_, entry.second, 32, {20 + first->getImageRect().w + 20, y},
                                                      secondColor);
        y += 70;

        labels.push_back(first);
        labels.push_back(second);
    }

    do {
        cursorPosition = cmm_->get_cursor_position();

        ExitButton.update(cursorPosition);
        pageTitle.update(cursorPosition);
        gameName.update(cursorPosition);

        if (ExitButton.isButtonPressed() || inputManager->quitRequested()) {
            logger_->info("Quit Statistics screen");
            break;
        }

        for (auto &label : labels) {
            label->update(cursorPosition);
        }

        //Update gaze position
        gaze_object.update(cursorPosition);

        // update the window when all the texture are displayed
        window_->update();

    } while (true);

    for (auto &label : labels) {
        core::utils::safe_delete(label);
    }
}

std::map<std::string, std::string> core::Statistics::initTranslation() {

    std::map<std::string, std::string> map;

    map["cases_pushed"] = "Nombre de cases decouvertes";
    map["level_loose"] = "Nombre de niveaux perdu";
    map["level_win"] = "Nombre de niveaux gagne";
    map["max_level"] = "Niveau maximal atteint";
    map["number_of_games"] = "Nombre de parties jouee";

    return map;
}

std::string core::Statistics::getTranslation(std::string key) {

    auto value = translation.find(key);

    if (value != translation.end()) {
        return value->second;
    }

    return key;
}
