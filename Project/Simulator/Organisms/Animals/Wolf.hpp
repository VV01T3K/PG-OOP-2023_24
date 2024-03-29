#pragma once

#include "@Animal.hpp"
class Wolf : public Animal {
   public:
    Wolf(World& world) : Animal(9, 5, world, Type::WOLF) {}
    Wolf(nlohmann::json json, World& world) : Animal(json, world) {}
    Animal* construct() const override { return new Wolf(world); }
};
