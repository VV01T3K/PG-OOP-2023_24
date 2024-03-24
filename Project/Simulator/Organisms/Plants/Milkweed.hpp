#pragma once

#include "@Plant.hpp"
class Milkweed : public Plant {
   public:
    Milkweed(World& world) : Plant(0, world, Type::MILKWEED) {}
    void draw() override { std::cout << "🌾"; }
    Plant* construct() const override { return new Milkweed(world); }

    void action() override {
        Plant::action();
        Plant::action();
        Plant::action();
    }
};
