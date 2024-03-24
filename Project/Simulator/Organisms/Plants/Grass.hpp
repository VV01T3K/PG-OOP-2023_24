#pragma once

#include "@Plant.hpp"
class Grass : public Plant {
   public:
    Grass(World& world) : Plant(0, world) {}
    void draw() override { std::cout << "🌿"; }
    Plant* construct() const override { return new Grass(world); }
};
