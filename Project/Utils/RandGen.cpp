#include "RandGen.hpp"

RandGen::RandGen() : gen(rng()) {}

RandGen& RandGen::getInstance() {
    static RandGen instance;
    return instance;
}

int RandGen::roll(int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}