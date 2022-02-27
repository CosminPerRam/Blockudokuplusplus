
#include "utilities.h"

#include <random>

int trueRandom::getNumberInBetween(unsigned a, unsigned b) {
    static std::random_device rd; // obtain a random number from hardware
    static std::mt19937 gen(rd()); // seed the generator

    std::uniform_int_distribution<> distr(a, b); // define the range

    return distr(gen);
}