#pragma once

#include "@Plant.hpp"
class Grass : public Plant {
   public:
    Grass(World& world) : Plant(0, world, Type::GRASS) {}
    Grass(nlohmann::json j, World& world) : Plant(j, world) {}
    void draw() override { std::cout << "🌿"; }
    Plant* construct() const override { return new Grass(world); }
};
