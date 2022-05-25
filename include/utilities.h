#pragma once

#include <sstream>

namespace random
{
	int getNumberInBetween(unsigned a, unsigned b);
}

namespace files
{
	std::stringstream getFileContents(const std::string& fileName);

	void writeToFile(const std::string& text, const std::string& fileName, bool overwrite = true);
}