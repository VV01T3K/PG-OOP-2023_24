#pragma once

#include "@Plant.hpp"
class Guarana : public Plant {
   public:
    Guarana(World& world) : Plant(0, world, Type::GUARANA) {}
    Guarana(nlohmann::json json, World& world) : Plant(json, world) {}
    Plant* construct() const override { return new Guarana(world); }

    bool collisionReaction(Organism& other) override {
        other.setPower(other.getPower() + 3);
        Die();
        world.addLog(other.getSymbol() + " ate " + getSymbol() +
                     " and gained 3 power!");
        return true;
    }
};
