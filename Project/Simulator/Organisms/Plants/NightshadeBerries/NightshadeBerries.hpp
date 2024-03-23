#pragma once

#include "../Plant.hpp"
class NightshadeBerries : public Plant {
   public:
    NightshadeBerries(int x, int y, World &world) : Plant(99, x, y, world) {}
    NightshadeBerries(Position position, World &world)
        : Plant(99, position, world) {}

    void collision(Organism &other) override {
        other.setAlive(false);
        this->setAlive(false);
    }
};
