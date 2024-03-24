#pragma once

#include "@Plant.hpp"
class Guarana : public Plant {
   public:
    Guarana(World& world) : Plant(0, world, Type::GUARANA) {}
    void draw() override { std::cout << "🍅"; }
    Plant* construct() const override { return new Guarana(world); }

    bool collisionReaction(Organism& other) override {
        other.setPower(other.getPower() + 3);
        Die();
        return true;
    }
};
