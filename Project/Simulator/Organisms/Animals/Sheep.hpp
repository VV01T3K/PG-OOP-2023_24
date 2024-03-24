#pragma once

#include "@Animal.hpp"
class Sheep : public Animal {
   public:
    Sheep(World& world) : Animal(4, 4, world, Type::SHEEP) {}
    Sheep(nlohmann::json json, World& world) : Animal(json, world) {}
    void draw() override { std::cout << "🐏"; }
    Animal* construct() const override { return new Sheep(world); }
};
