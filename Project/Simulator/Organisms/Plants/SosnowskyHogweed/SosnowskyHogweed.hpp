#pragma once

#include "../../Animals/CyberSheep/CyberSheep.hpp"
#include "../@Plant.hpp"

class CyberSheep;
class SosnowskyHogweed : public Plant {
   public:
    SosnowskyHogweed(World& world) : Plant(10, world) {}
    void draw() override { std::cout << "🍁"; }
    Plant* construct() const override { return new SosnowskyHogweed(world); }

    void action() override;

    bool collisionReaction(Organism& other) override;
};