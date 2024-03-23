#pragma once

#include "../Plant.hpp"
class Grass : public Plant {
   public:
    Grass(int x, int y, World &world) : Plant(0, x, y, world) {}
    Grass(Position position, World &world) : Plant(0, position, world) {}
};
