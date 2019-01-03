#include "Utils.h"
#include <fstream>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

std::string core::utils::readText(std::string filename)
{
	std::ifstream file(filename);

	if(!file.is_open())
	{
		return "";
	}

	std::string str((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());

	file.close();

	return str;
}

std::vector<std::string> core::utils::split(std::string str, std::string delim)
{
	std::vector<std::string> result;

	size_t pos = 0;
	std::string token;

	while ((pos = str.find(delim)) != std::string::npos) {
		token = str.substr(0, pos);
		result.push_back(token);
		str.erase(0, pos + delim.length());
	}

	if(result.empty())
	{
		result.push_back(str);
	}

	return result;
}

std::string core::utils::trim(std::string str)
{
	if (str.empty()) return str;
	std::string::size_type i, j;
	i = 0;
	while (i < str.size() && isspace(str[i])) ++i;
	if (i == str.size())
		return ""; // empty string
	j = str.size() - 1;

	while (isspace(str[j])) --j;
		return str.substr(i, j - i + 1);
}

int core::utils::randomInt(int min, int max)
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max); // distribution in range [min, max]

	return dist(rng);
}

bool core::utils::isInside(int x, int y, SDL_Rect rect)
{
	return x > rect.x && x < rect.x + 2 * rect.w && y > rect.y && y < rect.y + 2 * rect.h;
}

std::string core::utils::toLowerCase(std::string str) {

	std::string data = str;
	
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);

	return data;
}