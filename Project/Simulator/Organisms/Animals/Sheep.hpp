#pragma once

#include "@Animal.hpp"
class Sheep : public Animal {
   public:
    Sheep(World& world) : Animal(4, 4, world) {}
    void draw() override { std::cout << "🐏"; }
    Animal* construct() const override { return new Sheep(world); }
};
