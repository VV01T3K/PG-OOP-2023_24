#pragma once

// !! fix

#include "@Plant.hpp"
class SosnowskyHogweed : public Plant {
   public:
    SosnowskyHogweed(World& world) : Plant(10, world) {}
    void draw() override { std::cout << "🫚"; }
    Plant* construct() const override { return new SosnowskyHogweed(world); }

    void action() override {
        Plant::action();
        for (Tile* tile : tile->getNeighbours()) {
            if (tile->getOrganism() == nullptr) continue;
            if (typeid(*tile->getOrganism()) == typeid(Plant)) continue;
            if (typeid(*tile->getOrganism()) == typeid(CyberSheep)) continue;
            tile->getOrganism()->Die();
        }
    }

    void collisionReaction(Organism& other) override {
        if (typeid(other) == typeid(Plant)) return;
        if (typeid(other) == typeid(CyberSheep)) return;
        other.Die();
    }
};