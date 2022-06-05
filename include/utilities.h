
#pragma once

#include <sstream>

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
