#ifndef STATISTICSMANAGER_INCLUDED
#define STATISTICSMANAGER_INCLUDED

#include <string>
#include <map>
#include <spdlog/logger.h>

namespace core {
    /// This class is used to store statistics in the program
    /// A statistics can be incemented (ex number of game played), maximized (highest level reached)
    /// This class work the same as Config but without comments. It also re-wrote the file
    class StatisticsManager {
    public:

        /// Setup the statistics for the given name
        explicit StatisticsManager(std::string gameName);

        ~StatisticsManager();

        /// Increment the statistics for the given key by incrementBy
        void increment(std::string statName, int incrementBy);

        /// Set max value from the old one and the given value
        void setMaxOf(std::string statName, int value);

        /// Get a specific value
        /// If the value is not found, return the default value
        std::string getValue(std::string statName, std::string defaultValue);

        /// Load the configuration from the file
        void load();

        /// Write the modifications to the file
        void flush();

        /// Get all the statistics about this game
        /// This can be used for display purposes
        std::map<std::string, std::string> getStatistics();

    private:
        /// The name of the game
        std::string gameName;

        /// All the stored stats
        std::map<std::string, std::string> stats;

        /// the logger
        std::shared_ptr<spdlog::logger> logger_;
    };
}

#endif //CODE_STATISTICSMANAGER_H
