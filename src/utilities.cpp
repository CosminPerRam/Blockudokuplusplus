
#include "utilities.h"

#include <random>
#include <fstream>

int Random::getNumberInBetween(unsigned a, unsigned b) {
    static std::random_device rd; // obtain a random number from hardware
    static std::mt19937 gen(rd()); // seed the generator

    std::uniform_int_distribution<> distr(a, b); // define the range

    return distr(gen);
}

bool Files::exists(const char* fileName) {
    return std::ifstream(fileName).good();
}

void Files::create(const char* fileName) {
    std::ofstream fout(fileName);
}

void Files::erase(const char* fileName) {

    std::stringstream sstream;
    Files::write(sstream, fileName);
}

std::stringstream Files::read(const char* fileName) {
    std::ifstream fin(fileName);

    std::stringstream theStream;
    theStream << fin.rdbuf();

    return theStream;
}

void Files::write(std::stringstream& sstream, const char* fileName) {
    std::ofstream fout(fileName);

    fout << sstream.rdbuf();
}

void Files::append(std::stringstream& sstream, const char* fileName) {
    std::ofstream fout(fileName, std::ios_base::app);

    fout << sstream.rdbuf();
}

void Platform::setConsoleVisibility(bool state) {
#ifdef _WIN32
    ShowWindow(GetConsoleWindow(), state);
#endif
}