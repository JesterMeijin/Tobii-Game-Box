#include <spdlog/spdlog.h>
#include <fstream>
#include <iostream>
#include <string>

#include "StatisticsManager.h"
#include "Utils.h"

core::StatisticsManager::StatisticsManager(std::string gameName) :
        gameName(gameName) {
    logger_ = spdlog::get("root");
}

core::StatisticsManager::~StatisticsManager() = default;

std::map<std::string, std::string> core::StatisticsManager::getStatistics() {
    return stats;
}

void core::StatisticsManager::flush() {
    std::string fileName = "ressources/games/" + core::utils::toLowerCase(gameName) + "/statistics.txt";
    std::ofstream statFile(fileName);

    if (!statFile.is_open()) {
        logger_->warn("Game {} unable to open statistic file for writing", gameName);
    }

    logger_->info("Flushing statistics for game {}", gameName);

    for (auto &entry : stats) {
        logger_->debug("save state {}:{} for game {}", entry.first, entry.second, gameName);

        statFile << entry.first;
        statFile << "=";
        statFile << entry.second;
        statFile << "\n";
    }

    statFile.close();
}

void core::StatisticsManager::load() {

    std::string fileName = "ressources/games/" + core::utils::toLowerCase(gameName) + "/statistics.txt";
    std::ifstream statFile(fileName);

    if (!statFile.is_open()) {
        logger_->warn("Cannot open statistics file for game {}", gameName);
        return;
    }

    std::string line;

    while (std::getline(statFile, line)) {
        line = core::utils::trim(line);

        // Check if the line is empty
        if (line.empty()) {
            continue;
        }

        auto equalsChar = line.find("=");
        if (equalsChar == std::string::npos) {
            logger_->debug("Game {} Found invalid statistic line ()", gameName, line);
            continue;
        }

        std::string key = core::utils::trim(line.substr(0, equalsChar));
        std::string value = core::utils::trim(line.substr(equalsChar + 1, line.size()));

        stats[key] = value;

        logger_->info("Game {} Found valid statistic({}:{})", gameName, key, value);
    }

    statFile.close();
}

std::string core::StatisticsManager::getValue(std::string statName, std::string defaultValue) {

    auto oldValueIt = stats.find(statName);

    if (oldValueIt != stats.end()) {
        return oldValueIt->second;
    }

    return defaultValue;
}

void core::StatisticsManager::setMaxOf(std::string statName, int value) {

    auto oldValueIt = stats.find(statName);

    if (oldValueIt != stats.end()) {
        // a value exists
        int oldValue = std::stoi(oldValueIt->second);

        stats[statName] = std::to_string(value > oldValue ? value : oldValue);

    } else {
        stats[statName] = std::to_string(value);
    }
}

void core::StatisticsManager::increment(std::string statName, int incrementBy) {

    auto oldValueIt = stats.find(statName);

    if (oldValueIt != stats.end()) {
        // a value exists
        int oldValue = std::stoi(oldValueIt->second);

        stats[statName] = std::to_string(oldValue + incrementBy);

    } else {
        stats[statName] = std::to_string(incrementBy);
    }
}
