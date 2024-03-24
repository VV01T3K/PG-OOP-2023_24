#pragma once

#include "@Animal.hpp"
class Fox : public Animal {
   public:
    Fox(World& world) : Animal(3, 7, world, Type::FOX) {}
    Fox(nlohmann::json json, World& world) : Animal(json, world) {}
    void draw() override { std::cout << "🦊"; }
    Animal* construct() const override { return new Fox(world); }

    void action() override {
        std::vector<Tile*> neighbours = tile->getNeighbours();
        for (auto& neighbour : neighbours) {
            if (neighbour->isFree()) continue;
            if (neighbour->getOrganism()->getPower() <= power) continue;
            neighbours.erase(
                std::remove(neighbours.begin(), neighbours.end(), neighbour),
                neighbours.end());
        }
        Tile* target;
        if (neighbours.empty()) {
            target = tile->getRandomFreeNeighbour();
        } else {
            target = neighbours[RNG::roll(0, neighbours.size() - 1)];
        }
        move(target);
    };
};