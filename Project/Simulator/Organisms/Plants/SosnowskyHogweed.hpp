#pragma once

#include "@Plant.hpp"

class SosnowskyHogweed : public Plant {
   private:
    std::vector<std::string> killed;

   public:
    SosnowskyHogweed(World& world)
        : Plant(10, world, Type::SOSNOWSKY_HOGWEED) {}
    SosnowskyHogweed(nlohmann::json json, World& world) : Plant(json, world) {}
    Plant* construct() const override { return new SosnowskyHogweed(world); }

    void action() override {
        Plant::action();
        for (auto& neighbour : tile->getOccupiedNeighbours()) {
            if (dynamic_cast<Plant*>(neighbour->getOrganism()) != nullptr)
                continue;
            if (neighbour->getOrganism()->type == Type::CYBER_SHEEP) continue;

            neighbour->getOrganism()->Die();
            killed.push_back(neighbour->getOrganism()->getSymbol());
        }
        if (killed.size() > 0) {
            std::string log = getSymbol() + " killed ";
            for (size_t i = 0; i < killed.size(); i++) {
                log += killed[i];
                if (i != killed.size() - 1) log += ", ";
            }
            world.addLog(log + "!");
            killed.clear();
        }
    }

    bool collisionReaction(Organism& other) override {
        if (dynamic_cast<Plant*>(&other) != nullptr) return false;
        if (other.type == Type::CYBER_SHEEP) return false;
        other.Die();
        Die();
        world.addLog(other.getSymbol() + " ate " + getSymbol() + " and died!");
        return true;
    }
};