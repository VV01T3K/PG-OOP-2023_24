#pragma once

#include "Animal.hpp"
class Wolf : public Animal {
   public:
    Wolf(int x, int y, World &world) : Animal(9, 5, x, y, world) {}
    Wolf(Position position, World &world) : Animal(9, 5, position, world) {}
};