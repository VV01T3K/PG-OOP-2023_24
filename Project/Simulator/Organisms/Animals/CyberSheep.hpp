#pragma once

#include "@Animal.hpp"

class CyberSheep : public Animal {
   public:
    CyberSheep(World& world) : Animal(11, 4, world, Type::CYBER_SHEEP) {}
    CyberSheep(nlohmann::json j, World& world) : Animal(j, world) {}
    void draw() override { std::cout << "🤖"; }
    Animal* construct() const override { return new CyberSheep(world); }

    void action() override {
        size_t index = seekClosestSosnowskyHogweed();
        if (index == -1) {
            Animal::action();
            return;
        }
        Tile* target = nextTileToSosnowskyHogweed(index);
        if (target == nullptr) {
            Animal::action();
            return;
        }
        move(target);
    }

   private:
    size_t seekClosestSosnowskyHogweed() {
        size_t index = -1;
        size_t min_distance = -1;
        for (size_t i = 0; i < world.getOrganimsCount(); i++) {
            Organism* target = world.getOrganism(i);
            if (target->type == Type::SOSNOWSKY_HOGWEED) {
                size_t distance =
                    tile->getDistanceTo(target->getTile(), world.getWidth());
                if (distance < min_distance) {
                    min_distance = distance;
                    index = i;
                }
            }
        }
        return index;
    }

    Tile* nextTileToSosnowskyHogweed(size_t index) {
        Tile* target = world.getOrganism(index)->getTile();
        const size_t distance = tile->getDistanceTo(target, world.getWidth());
        std::vector<Tile*> possible_moves;
        std::vector<Tile*> neighbours = tile->getNeighbours();
        for (auto neighbour : neighbours) {
            if (neighbour->getDistanceTo(target, world.getWidth()) < distance) {
                possible_moves.push_back(neighbour);
            }
        }
        if (possible_moves.empty()) return nullptr;
        return possible_moves[RNG::roll(0, possible_moves.size() - 1)];
    }
};
