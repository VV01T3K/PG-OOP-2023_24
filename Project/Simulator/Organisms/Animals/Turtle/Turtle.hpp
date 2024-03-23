#pragma once
#include <typeinfo>

#include "../Animal.hpp"
class Turtle : public Animal {
   public:
    Turtle(int x, int y, World &world) : Animal(2, 1, x, y, world) {}
    Turtle(Position position, World &world) : Animal(2, 1, position, world) {}

    void action() override {
        if (world.rng.roll(0, 3) == 0) Animal::action();
    }

    void collision(Organism &other) override {
        if (typeid(other) == typeid(Animal)) {
            if (other.getPower() < 5) {
                static_cast<Animal &>(other).undoMove();
            }
        } else {
            Animal::collision(other);
        }
    }
};