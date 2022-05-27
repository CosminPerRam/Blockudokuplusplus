#pragma once

#include <sstream>

namespace Random
{
	int getNumberInBetween(unsigned a, unsigned b);
}

namespace Files
{
	std::stringstream getFileContents(const std::string& fileName);

	void writeToFile(const std::string& text, const std::string& fileName, bool overwrite = true);
}