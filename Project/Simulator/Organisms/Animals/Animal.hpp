#pragma once

#include <random>

#include "../../../Utils/RandGen.hpp"
#include "../../Position.hpp"
#include "../Organism.hpp"

class Animal : public Organism {
   private:
    RandGen& rng;
    Position oldPosition;

    enum class Direction : uint8_t { UP, DOWN, LEFT, RIGHT };

    void move(Direction direction) {
        switch (direction) {
            case Direction::UP:
                if (position.y > 0) position.y--;
                break;
            case Direction::DOWN:
                if (position.y < world.getHeight() - 1) position.y++;
                break;
            case Direction::LEFT:
                if (position.x > 0) position.x--;
                break;
            case Direction::RIGHT:
                if (position.x < world.getWidth() - 1) position.x++;
                break;
        }
    }

   public:
    Animal(int power, int initiative, int x, int y, World& world)
        : Organism(power, initiative, x, y, world),
          rng(RandGen::getInstance()),
          oldPosition(x, y) {}
    Animal(int power, int initiative, Position position, World& world)
        : Organism(power, initiative, position, world),
          rng(RandGen::getInstance()),
          oldPosition(position) {}

    void action() override {
        oldPosition = position;
        while (oldPosition == position) {
            move(static_cast<Direction>(
                rng.roll(0, 3)));  // 0-UP, 1-DOWN, 2-LEFT, 3-RIGHT
        }
    }
    void undoAction() override { position = oldPosition; }
    void collision(Organism& other) override {
        if (other == *this) {
            world.addOrganism(new Animal(power, initiative, position, world));
            this->undoAction();
            other.skipTurn();
        } else if (power < other.getPower()) {
            this->die();
        } else {
            other.die();
        }
    }
    void draw() override {}
};