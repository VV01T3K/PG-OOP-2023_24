#pragma once
#include <typeinfo>

#include "../Animal.hpp"
class CyberSheep : public Animal {
   public:
    CyberSheep(int x, int y, World &world) : Animal(11, 4, x, y, world) {}
    CyberSheep(Position position, World &world)
        : Animal(11, 4, position, world) {}
};