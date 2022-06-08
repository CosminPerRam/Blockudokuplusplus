
#pragma once

#include <sstream>

#ifdef _WIN32
#define SUPPORTS_CONSOLE_HIDING 1
#include <windows.h>
#else
#define SUPPORTS_CONSOLE_HIDING 0
#endif

namespace Random
{
	int getNumberInBetween(unsigned a, unsigned b);
}

namespace Files
{
	bool exists(const char* fileName);
	void create(const char* fileName);
	void erase(const char* fileName);

	std::stringstream read(const char* fileName);
	void write(std::stringstream& sstream, const char* fileName);
	void append(std::stringstream& sstream, const char* fileName);
}

namespace Platform
{
	void setConsoleVisibility(bool state);
}