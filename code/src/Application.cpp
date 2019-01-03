#include <iostream>
#include <SDL/SDL.h>
#include <sstream>
#include <experimental/filesystem> // or #include <filesystem>

#include "Application.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "GazeObject.h"
#include "game/remember/RememberGame.h"
#include "Utils.h"
#include "MusicManager.h"
#include "Settings.h"

core::Application::Application() :
        window_(nullptr),
        config_(nullptr),
        frame_counter_(nullptr),
        cursor_movement_manager_(nullptr),
        logger_(nullptr),
        inputManager(nullptr),
        menu_(nullptr) {
}

core::Application::~Application() {

    for (auto game : games_) {
        utils::safe_delete(game);
    }

	utils::safe_delete(window_);
	utils::safe_delete(config_);
	utils::safe_delete(cursor_movement_manager_);
	utils::safe_delete(frame_counter_);
	utils::safe_delete(menu_);
	utils::safe_delete(musicManager);


    TTF_Quit();
    SDL_Quit();
}

void core::Application::run(int argc, char *argv[]) {
    init(argc, argv);

    GazeObject gaze_object(window_);

    musicManager->playInBackground("ressources/sound/background.mp3");

    //Main loop
    while (true) {
        inputManager->update();
        auto gaze_position = cursor_movement_manager_->get_cursor_position();


        logger_->trace("Cursor position x : {}, y : {}", gaze_position.x, gaze_position.y);

        // update menu
        bool menuQuitRequested = menu_->update(gaze_position);

        if (inputManager->quitRequested() || menuQuitRequested) {
            break;
        }

        //Update gaze position
        gaze_object.update(gaze_position);

        // update the window when all the texture are displayed
        window_->update();

        // Always delay next frame at th end if needed
        frame_counter_->delay_if_needed();
    }

	config_->flush();
}

void core::Application::init(int argc, char *argv[]) {
    //init logger
    try {
        // create log dir if it doesn't exist
        namespace fs = std::experimental::filesystem;
        std::string logDirectory = "log";

        if (!fs::is_directory(logDirectory) || !fs::exists(logDirectory)) { // Check if logDirectory exists
            fs::create_directory(logDirectory); // create logDirectory
        }

        spdlog::init_thread_pool(1800, 1);
        spdlog::set_pattern("[%D %H:%M:%S] [thread %t] [%l] %v");

        auto time = std::chrono::system_clock::now();

        std::stringstream log_file_name;
        log_file_name << "log/log_" << time.time_since_epoch().count() << ".log";

        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
        sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_file_name.str()));

        logger_ = std::make_shared<spdlog::logger>("root", begin(sinks), end(sinks));

        logger_->set_level(spdlog::level::debug);

        //register it if you need to access it globally
        spdlog::register_logger(logger_);

    } catch (spdlog::spdlog_ex &ex) {
        std::cerr << "Error initializing logger : " << ex.what() << std::endl;
        throw std::exception("Logger init_device problem");
    }

    logger_->debug("Logger initialized");

    // init config
    config_ = new Config(argc, argv);
    config_->load();

	//init SDL graphics
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		logger_->error("Error while initializing SDL : {}", SDL_GetError());

        throw std::exception();
    }

	// init SDL ttf
	if (TTF_Init() == -1) {
		logger_->error("Error while initializing SDL ttf : {}", SDL_GetError());

        throw std::exception();
    }

	// init window
	window_ = new core::Window(config_);

    // init cursor manager
    cursor_movement_manager_ = new CursorMovementManager(window_, config_);

    logger_->debug("Cursors initialized");

    SDL_ShowCursor(SDL_DISABLE);

    // init InputManager
    inputManager = InputManager::getInstance();

	//init audio
	musicManager = new MusicManager(config_->get_bool("music_default_enable", true));


	// init framecounter
	frame_counter_ = new FrameCounter(config_->get_int("frame_rate", 60));

	// init games 
	games_.push_back(new game::rg::RememberGame(window_, cursor_movement_manager_, "Remember", config_, musicManager));
	games_.push_back(new game::rg::RememberGame(window_, cursor_movement_manager_, "Remember", config_, musicManager));

	// init other view
	Statistics* statistics_ = new Statistics(window_, musicManager, cursor_movement_manager_, config_);
	Leaderboard* leaderboard_ = new Leaderboard(window_, musicManager, cursor_movement_manager_, config_);
	Settings* settings_ = new Settings(window_, musicManager, cursor_movement_manager_, config_);

	// init menu
	menu_ = new Menu(window_, musicManager, games_, statistics_, leaderboard_, settings_);

    logger_->info("Init done");
}