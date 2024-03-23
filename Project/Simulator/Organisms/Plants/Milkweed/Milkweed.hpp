#pragma once

#include "../Plant.hpp"
class Milkweed : public Plant {
   public:
    Milkweed(int x, int y, World &world) : Plant(0, x, y, world) {}
    Milkweed(Position position, World &world) : Plant(0, position, world) {}

    virtual void action() override {
        Plant::action();
        Plant::action();
        Plant::action();
    }
};
