#pragma once

#include "../Animal.hpp"

class Antelope : public Animal {
   public:
    Antelope(int x, int y, World &world) : Animal(4, 4, x, y, world) {}
    Antelope(Position position, World &world) : Animal(4, 4, position, world) {}

    void action() override {
        oldPosition = position;
        while (oldPosition == position) {
            move(static_cast<Direction>(
                rng.roll(0, 3)));  // 0-UP, 1-DOWN, 2-LEFT, 3-RIGHT
        }
    }
    void collision(Organism &other) override {
        if (other.getPower() > power) {
            if (rng.roll(0, 1) == 0) {
                position = oldPosition;
            } else {
                Animal::collision(other);
            }
        } else {
            Animal::collision(other);
        }
    }
};