#pragma once

#include "@Plant.hpp"
class SosnowskyHogweed : public Plant {
   public:
    SosnowskyHogweed(World& world) : Plant(10, world) {}
    void draw() override { std::cout << " ⚛"; }
    Plant* construct() const override { return new SosnowskyHogweed(world); }

    void action() override {
        Plant::action();
        for (auto& neighbour : tile->getOccupiedNeighbours()) {
            if (dynamic_cast<Plant*>(neighbour->getOrganism()) != nullptr)
                continue;
            if (typeid(*neighbour->getOrganism()) == typeid(CyberSheep))
                continue;

            neighbour->getOrganism()->Die();
        }
    }

    void collisionReaction(Organism& other) override {
        if (dynamic_cast<Plant*>(&other) != nullptr) return;
        if (typeid(other) == typeid(CyberSheep)) return;
        other.Die();
    }
};