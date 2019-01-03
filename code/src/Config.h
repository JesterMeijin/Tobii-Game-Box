#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED
#include <string>
#include <map>
#include <spdlog/logger.h>

/// The configuration of the software
/// It read the config.ini file in readonly mode
/// Each config line can be commented with # char or leaved empty
/// Other line are configuration lines with key and value (key=value format)
class Config
{
public:
	/// Load the configuration with the execution parameters
	Config(int argc, char* argv[]);
	~Config();

	/// Load the config file
	/// This parse the config.ini file and store each pair of key value inside the values attribute
	void load();

	/// Write the modifications to the file
	void flush();

	/// This method return the value associated with the given key with a string format
	std::string get_string(std::string key, std::string defaultValue);

	/// This method return the value associated with the given key with a boolean format
	bool get_bool(std::string key, bool defaultValue);

	/// This method return the value associated with the given key with a int format
	int get_int(std::string key, int defaultValue);

	/// This method change the config of the key with the boolean in parameter
	void set_bool(std::string key, bool value);

private:

	/// Store all the key value pairs as string
	std::map<std::string, std::string> values;

	/// The filename of the config
	std::string fileName;

	/// The logger
	std::shared_ptr<spdlog::logger> logger_;
};

#endif // CONFIG_INCLUDED
