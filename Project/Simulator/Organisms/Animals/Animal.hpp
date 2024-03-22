#pragma once

#include <random>

#include "../../../Utils/RandGen.hpp"
#include "../../Position.hpp"
#include "../Organism.hpp"

class Animal : public Organism {
   private:
    RandGen& rng = RandGen::getInstance();
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

    void move() {
        Position oldPosition = position;
        while (oldPosition == position) {
            move(static_cast<Direction>(
                rng.roll(0, 3)));  // 0-UP, 1-DOWN, 2-LEFT, 3-RIGHT
        }
    }

   public:
    Animal(/* args */);
    ~Animal();
    void action() override{

    };
    void collision(Organism& organism) override;
};