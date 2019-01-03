#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED
#include <string>
#include <vector>
#include <random>
#include <SDL/SDL.h>

namespace core
{

/// this namespace contains a bunch of utils function that are not provided by the std library
namespace utils
{
	/// Read all the content of a file
	std::string readText(std::string filename);

	/// Delete safeully a pointer by deleting it and passing it to null_ptr
	template<typename T>
	void safe_delete(T*& obj) {
		delete obj;
		obj = nullptr;
	}

	/// split a string into multiples string using a delimiter
	std::vector<std::string> split(std::string str, std::string delim);

	/// Remove leading and end spaces from a string
	std::string trim(std::string str);

	/// return the string to lower case
	std::string toLowerCase(std::string str);

	/// get a random int between the two borne
	int randomInt(int min, int max);

	/// Check if the given coordinates are inside the given rectangle
	bool isInside(int x, int y, SDL_Rect rect);
}
}

#endif // UTILS_INCLUDED