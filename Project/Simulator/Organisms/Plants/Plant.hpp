#pragma once

#include <random>

#include "../../../Utils/RandGen.hpp"
#include "../../Position.hpp"
#include "../Organism.hpp"

class Plant : public Organism {
   private:
    RandGen& rng;

   public:
    Plant(int power, int initiative, int x, int y, World& world)
        : Organism(power, initiative, x, y, world),
          rng(RandGen::getInstance()) {}
    Plant(int power, int initiative, Position position, World& world)
        : Organism(power, initiative, position, world),
          rng(RandGen::getInstance()) {}

    virtual void action() = 0;
    virtual void collision(Organism& other) = 0;
    virtual void draw() = 0;
};