#pragma once

#include "../Animal.hpp"
class Fox : public Animal {
   public:
    Fox(int x, int y, World &world) : Animal(3, 7, x, y, world) {}
    Fox(Position position, World &world) : Animal(3, 7, position, world) {}

    void action() override {
        oldPosition = position;
        while (oldPosition == position) {
            move(static_cast<Direction>(
                world.rng.roll(0, 3)));  // 0-UP, 1-DOWN, 2-LEFT, 3-RIGHT
            if (world.getOrganismAt(position) != nullptr &&
                world.getOrganismAt(position)->getPower() > power) {
                undoMove();
            }
        }
    }
};