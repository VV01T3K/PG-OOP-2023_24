#pragma once

#include "@Plant.hpp"
class WolfBerries : public Plant {
   public:
    WolfBerries(World& world) : Plant(99, world, Type::WOLF_BERRIES) {}
    WolfBerries(nlohmann::json json, World& world) : Plant(json, world) {}
    Plant* construct() const override { return new WolfBerries(world); }

    bool collisionReaction(Organism& other) override {
        other.Die();
        Die();
        world.addLog(other.getSymbol() + " ate " + getSymbol() + " and died!");
        return true;
    }
};
