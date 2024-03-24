#pragma once

#include "@Animal.hpp"
class Human : public Animal {
   public:
    Human(World& world) : Animal(9, 5, world) {}
    void draw() override { std::cout << "🧑"; }
    Animal* construct() const override { return new Human(world); }
};
