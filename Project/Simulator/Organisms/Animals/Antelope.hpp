#pragma once

#include "@Animal.hpp"
class Antelope : public Animal {
   public:
    Antelope(World& world) : Animal(4, 4, world) {}
    void draw() override { std::cout << "🦌"; }
    Animal* construct() const override { return new Antelope(world); }
};
