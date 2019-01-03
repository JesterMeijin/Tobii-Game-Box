#ifndef MUSICMANAGER_INCLUDED
#define MUSICMANAGER_INCLUDED

#include <SDL/SDL_mixer.h>
#include <spdlog/logger.h>

namespace core {

    /// This class is in charge of playing sounds in the application
    /// You can play a sound in the background or pay a sfx (simple sound for one action)
    /// MP3, OGG, WAV and others file format are acceptable
    class MusicManager {
    public:

        /// Build the music manager by saying if it's enable by default
        explicit MusicManager(bool defaultEnable);

        /// Free all the music resources
        ~MusicManager();

        /// Enable or disable the music
        void enable(bool enable);

        /// Play a music in the background
        /// If the music is finished, the program loop it
        void playInBackground(std::string musicPath);

        /// stop the played music
        void stopBackground();

        /// Load the sfx with the given path
        Mix_Chunk* loadSFX(std::string path);

        /// free the given sfx
        void freeSFX(Mix_Chunk* sfx);

        /// Play the sfx
        void playSFX(Mix_Chunk* sfx);

    private:
        /// The logger
        std::shared_ptr<spdlog::logger> logger_;

        /// Initialization status
        bool isInit;

        /// Enable status of the music
        bool isEnable;

        /// The background music
        Mix_Music* music;
    };
}

#endif //MUSICMANAGER_INCLUDED
