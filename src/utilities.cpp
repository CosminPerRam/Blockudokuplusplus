
#include "utilities.h"

#include <random>
#include <fstream>

int trueRandom::getNumberInBetween(unsigned a, unsigned b) {
    static std::random_device rd; // obtain a random number from hardware
    static std::mt19937 gen(rd()); // seed the generator

    std::uniform_int_distribution<> distr(a, b); // define the range

    return distr(gen);
}

std::stringstream files::getFileContents(const std::string& fileName) {
    std::ifstream fin(fileName);

    std::stringstream theStream;
    theStream << fin.rdbuf();

    return theStream;
}

void files::writeToFile(const std::string& text, const std::string& fileName, bool overwrite) {
    std::ofstream fout;

    if (overwrite)
        fout.open(fileName);
    else
        fout.open(fileName, std::ios_base::app);

    fout << text;
}