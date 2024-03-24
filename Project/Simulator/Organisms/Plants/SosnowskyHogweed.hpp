#pragma once

#include "@Plant.hpp"
class SosnowskyHogweed : public Plant {
   public:
    SosnowskyHogweed(World& world) : Plant(10, world) {}
    void draw() override { std::cout << "🫚"; }
    Plant* construct() const override { return new SosnowskyHogweed(world); }

    void action() override {
        Plant::action();
        for (Tile* tile : tile->getNeighbours())
            if (!tile->isFree()) tile->getOrganism()->Die();
    }

    void collisionReaction(Organism& other) override { other.Die(); }
};
