#pragma once

#include "../../Plants/SosnowskyHogweed/SosnowskyHogweed.hpp"
#include "../@Animal.hpp"
class CyberSheep : public Animal {
   private:
    size_t getDistanceTo(Tile* tile);
    size_t seekClosestSosnowskyHogweed();
    Tile* nextTileToSosnowskyHogweed(size_t index);

   public:
    CyberSheep(World& world) : Animal(11, 4, world) {}
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

    bool collisionReaction(Organism& other) override;
};
