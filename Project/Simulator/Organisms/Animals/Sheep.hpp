#pragma once

#include "Animal.hpp"
class Sheep : public Animal {
   public:
    Sheep(int x, int y, World &world) : Animal(4, 4, x, y, world) {}
    Sheep(Position position, World &world) : Animal(4, 4, position, world) {}
};