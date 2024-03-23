#pragma once
#include <typeinfo>

#include "../../Animals/CyberSheep/CyberSheep.hpp"
#include "../Plant.hpp"

class SosnowskyHogweed : public Plant {
   public:
    SosnowskyHogweed(int x, int y, World &world) : Plant(10, x, y, world) {}
    SosnowskyHogweed(Position position, World &world)
        : Plant(10, position, world) {}

    void collision(Organism &other) override {
        if (typeid(other) != typeid(CyberSheep)) other.setAlive(false);
        this->setAlive(false);
    }
};