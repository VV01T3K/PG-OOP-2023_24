#pragma once

#include "../Plant.hpp"
class Guarana : public Plant {
   public:
    Guarana(int x, int y, World &world) : Plant(0, x, y, world) {}
    Guarana(Position position, World &world) : Plant(0, position, world) {}

    virtual void collision(Organism &other) override {
        other.setPower(other.getPower() + 3);
        this->setAlive(false);
    }
};
