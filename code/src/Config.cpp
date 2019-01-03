#include "Config.h"
#include <fstream>
#include <spdlog/spdlog.h>
#include <iostream>
#include "Utils.h"

Config::Config(int argc, char* argv[]):
fileName("ressources/config.ini"),
values()
{
	logger_ = spdlog::get("root");

	//TODO Find argument and store them by key value
}

Config::~Config()
{
}

void Config::load()
{
	std::ifstream myfile(fileName);

	if(!myfile.is_open())
	{
		logger_->warn("No config file found");
		return;
	}

	std::string line;
	while(std::getline(myfile, line))
	{
		line = core::utils::trim(line);

		// Check if the line is empty or a comment
		if(line.empty() || line.at(0) == '#')
		{
			continue;
		}

		// remove unnecessary comment at the end of the config line
		auto comment = line.find("#");
		if(comment != std::string::npos)
			line = line.substr(0, comment);

		auto equalsChar = line.find("=");
		if(equalsChar == std::string::npos)
		{
			logger_->debug("Found invalid config line ({})", line);
			continue;
		}

		std::string key = core::utils::trim(line.substr(0, equalsChar));
		std::string value = core::utils::trim(line.substr(equalsChar+1, line.size()));

		values[key] = value;

		logger_->info("Found valid config line ({}:{})", key, value);
	}

	myfile.close();
}

void Config::flush()
{
	std::ofstream myfile(fileName);

	if (!myfile.is_open())
	{
		logger_->warn("No config file found");
		return;
	}

	logger_->info("Flushing config");

	for (auto &entry : values) {
		logger_->debug("save state {}:{}*", entry.first, entry.second);

		myfile << entry.first;
		myfile << "=";
		myfile << entry.second;
		myfile << "\n";
	}

	myfile.close();
}

std::string Config::get_string(std::string key, std::string defaultValue)
{
	auto it = values.find(key);

	if(it != values.end())
	{
		return it->second;
	}

	return defaultValue;
}

bool Config::get_bool(std::string key, bool defaultValue)
{
	auto it = values.find(key);

	if (it != values.end())
	{
		// if the value is in { true, yes, 1 }
		std::string value(it->second);
		if (value == "true" || value == "yes" || value == "1")
			return true;

		return false;
	}

	return defaultValue;
}

void Config::set_bool(std::string key, bool value)
{
	auto it = values.find(key);

	// replace the current value with the new one
	if (it != values.end())
		values[key] = (value == 0 ? "false" : "true");
}

int Config::get_int(std::string key, int defaultValue)
{
	auto it = values.find(key);

	if (it != values.end())
	{
		return std::stoi(it->second);
	}

	return defaultValue;
}
