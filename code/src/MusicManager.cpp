#include <SDL/SDL.h>
#include <spdlog/spdlog.h>
#include "MusicManager.h"

core::MusicManager::MusicManager(bool enable) {

    logger_ = spdlog::get("root");
    isInit = true;

    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
        logger_->error("Couldn't start Audio {}", SDL_GetError());
        isInit = false;
    }

    int flags = MIX_INIT_OGG | MIX_INIT_MP3;
    if (isInit && (Mix_Init(flags) & flags) != flags) {
        logger_->error("Couldn't start sdl mix {}", Mix_GetError());
        isInit = false;
    }
    if (isInit && -1 == Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, // audio rate
                                      MIX_DEFAULT_FORMAT,    // format
                                      2,                     // channels
                                      4096))                 // buffers
    {
        logger_->error("Couldn't open sdl mixer {}", Mix_GetError());

        isInit = false;
    }

    if (isInit)
        Mix_AllocateChannels(16);

    isEnable = enable && isInit;

    logger_->info("Init music done isInit {}, isEnable {}", isInit, isEnable);
}

core::MusicManager::~MusicManager() {
    logger_->info("Free music manager");
    if (isInit) {
        Mix_AllocateChannels(0); // Frees all allocated channels

        Mix_CloseAudio();
    }
}

void core::MusicManager::enable(bool enable) {
    logger_->info("Set music {}", enable ? "enable" : "disable");
    isEnable = enable;

	if (isEnable)
		playInBackground("ressources/sound/background.mp3");
	else
		stopBackground();
}

void core::MusicManager::stopBackground() {
    Mix_HaltMusic();
}

void core::MusicManager::playInBackground(std::string musicPath) {

    if(!isEnable) {
        return;
    }

    music = Mix_LoadMUS(musicPath.c_str());
    if(music == nullptr) {
        logger_->error("Couldn't load music for '{}'", musicPath);
    }

    if (Mix_FadeInMusic(music, -1, 500)) {
        logger_->error("Couldn't play music for '{}'", musicPath);
    }
}

Mix_Chunk* core::MusicManager::loadSFX(std::string path) {

    logger_->info("Loading sfx {}", path);

    Mix_Chunk* sfx = Mix_LoadWAV(path.c_str());

    if(sfx == nullptr) {
        logger_->warn("Unable to load sfx {} error {}", path, Mix_GetError());
    }

    return sfx;
}

void core::MusicManager::freeSFX(Mix_Chunk *sfx) {

    logger_->debug("free sfx");

    if (sfx != nullptr)
        Mix_FreeChunk(sfx);
}

void core::MusicManager::playSFX(Mix_Chunk *sfx) {

    if(!isEnable) {
        return;
    }

    if(sfx != nullptr) {
        logger_->debug("Playing sfx");
        if(Mix_PlayChannel(-1, sfx, 0) == -1) {
            logger_->warn("Playing sound didn't work {}", Mix_GetError());
        }
    }
}
