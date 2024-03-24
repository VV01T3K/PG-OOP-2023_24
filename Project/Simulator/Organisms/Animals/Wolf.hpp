#pragma once

#include "@Animal.hpp"
class Wolf : public Animal {
   public:
    Wolf(World& world) : Animal(9, 5, world, Type::WOLF) {}
    Wolf(nlohmann::json j, World& world) : Animal(j, world) {}
    void draw() override { std::cout << "🐺"; }
    Animal* construct() const override { return new Wolf(world); }
};
