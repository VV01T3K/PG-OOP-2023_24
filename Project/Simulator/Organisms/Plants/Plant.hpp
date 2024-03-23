#pragma once

#include <random>

#include "../../Position.hpp"
#include "../Organism.hpp"

class Plant : public Organism {
   public:
    Plant(int power, int x, int y, World& world)
        : Organism(power, 0, x, y, world) {}
    Plant(int power, Position position, World& world)
        : Organism(power, 0, position, world) {}

    virtual void action() override {
        if (world.rng.roll(0, 99) < 5) {
            Position newPosition = position;
            while (newPosition == position || world.isOccupied(newPosition)) {
                newPosition = position;
                switch (static_cast<Direction>(world.rng.roll(0, 3))) {
                    case Direction::UP:
                        newPosition.y = position.y - 1;
                        break;
                    case Direction::DOWN:
                        newPosition.y = position.y + 1;
                        break;
                    case Direction::LEFT:
                        newPosition.x = position.x - 1;
                        break;
                    case Direction::RIGHT:
                        newPosition.x = position.x + 1;
                        break;
                }
            }
            world.addOrganism(new Plant(power, newPosition, world));
        }
    }
    virtual void collision(Organism& other) {}
    virtual void draw() override {}
};