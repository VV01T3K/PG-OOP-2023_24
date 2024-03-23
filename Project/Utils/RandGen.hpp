#pragma once
#include <random>

class RandGen {
   public:
    static RandGen& getInstance();

    int roll(int min, int max);

   private:
    std::random_device rng;
    std::mt19937 gen;

    RandGen();
    RandGen(const RandGen&) = delete;
    void operator=(const RandGen&) = delete;
};