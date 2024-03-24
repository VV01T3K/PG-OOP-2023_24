#pragma once

#include "@Animal.hpp"
class Fox : public Animal {
   public:
    Fox(World& world) : Animal(3, 7, world) {}
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
        if (neighbours.empty()) return;
        Tile* target = neighbours[rng.roll(0, neighbours.size())];
        move(target);
    };
};