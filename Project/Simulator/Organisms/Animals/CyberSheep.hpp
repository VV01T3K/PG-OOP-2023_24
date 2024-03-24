#pragma once

#include "@Animal.hpp"
class CyberSheep : public Animal {
   public:
    CyberSheep(World& world) : Animal(11, 4, world) {}
    void draw() override { std::cout << "🤖"; }
    Animal* construct() const override { return new CyberSheep(world); }
};
