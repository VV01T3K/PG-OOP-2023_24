#pragma once

#include "@Plant.hpp"

class SosnowskyHogweed : public Plant {
   public:
    SosnowskyHogweed(World& world)
        : Plant(10, world, Type::SOSNOWSKY_HOGWEED) {}
    SosnowskyHogweed(nlohmann::json j, World& world) : Plant(j, world) {}
    void draw() override { std::cout << "🍁"; }
    Plant* construct() const override { return new SosnowskyHogweed(world); }

    void action() override {
        Plant::action();
        for (auto& neighbour : tile->getOccupiedNeighbours()) {
            if (dynamic_cast<Plant*>(neighbour->getOrganism()) != nullptr)
                continue;
            if (neighbour->getOrganism()->type == Type::CYBER_SHEEP) continue;

            neighbour->getOrganism()->Die();
        }
    }

    bool collisionReaction(Organism& other) override {
        if (dynamic_cast<Plant*>(&other) != nullptr) return false;
        if (other.type == Type::CYBER_SHEEP) return false;
        other.Die();
        Die();
        return true;
    }
};