#pragma once

#include "@Plant.hpp"
class WolfBerries : public Plant {
   public:
    WolfBerries(World& world) : Plant(99, world) {}
    void draw() override { std::cout << "🫐 "; }
    Plant* construct() const override { return new WolfBerries(world); }

    void collisionReaction(Organism& other) override {
        other.Die();
        Die();
    }
};
