#pragma once

#include "@Plant.hpp"
class Grass : public Plant {
   public:
    Grass(World& world) : Plant(0, world, Type::GRASS) {}
    void draw() override { std::cout << "🌿"; }
    Plant* construct() const override { return new Grass(world); }
};
