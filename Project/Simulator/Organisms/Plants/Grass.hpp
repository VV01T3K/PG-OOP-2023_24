#pragma once

#include "@Plant.hpp"
class Grass : public Plant {
   public:
    Grass(World& world) : Plant(0, world, Type::GRASS) {}
    Grass(nlohmann::json json, World& world) : Plant(json, world) {}
    Plant* construct() const override { return new Grass(world); }
};
