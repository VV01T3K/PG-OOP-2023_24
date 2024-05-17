#pragma once
#include <random>

class RNG {
   private:
    std::random_device rng = std::random_device();
    std::mt19937 gen = std::mt19937(rng());

   public:
    static int_fast64_t roll(int_fast64_t min, int_fast64_t max) {
        static RNG instance;
        std::uniform_int_distribution<int_fast64_t> dist(min, max);
        return dist(instance.gen);
    }

    RNG() = default;
    ~RNG() = default;
};