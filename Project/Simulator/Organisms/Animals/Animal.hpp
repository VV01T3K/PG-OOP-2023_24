#pragma once

#include <iostream>
#include <random>

#include "../../Position.hpp"
#include "../Organism.hpp"

class Animal : public Organism {
   protected:
    Position oldPosition;

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
        : Organism(power, initiative, x, y, world), oldPosition(x, y) {}
    Animal(int power, int initiative, Position position, World& world)
        : Organism(power, initiative, position, world), oldPosition(position) {}

    virtual void action() override {
        oldPosition = position;
        while (oldPosition == position) {
            move(static_cast<Direction>(
                world.rng.roll(0, 3)));  // 0-UP, 1-DOWN, 2-LEFT, 3-RIGHT
        }
    }
    virtual void undoMove() { position = oldPosition; }
    virtual void collision(Organism& other) override {
        if (other == *this) {
            world.addOrganism(new Animal(power, initiative, position, world));
            this->undoMove();
            other.skipTurn();
            std::cout << "New animal born at " << position << std::endl;
        } else if (power < other.getPower()) {
            this->die();
        } else {
            other.die();
        }
    }
    virtual void draw() override {}
};