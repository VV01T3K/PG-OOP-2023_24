#pragma once

#include "Animal.hpp"
class Dog : public Animal {
   public:
    Dog(World& world) : Animal(6, 4, world) {}
    void draw() override { std::cout << "🐶"; }
    Animal* construct() const override { return new Dog(world); }
};
