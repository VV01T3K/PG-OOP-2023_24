#pragma once

#include "@Animal.hpp"
class Turtle : public Animal {
   public:
    Turtle(World& world) : Animal(10, 1, world) {}
    void draw() override { std::cout << "🐢"; }
    Animal* construct() const override { return new Turtle(world); }

    void action() override {
        // 75% chance to skip turn
        if (rng.roll(0, 100) < 75) return;
        return;
        Animal::action();
    };

    void collisionReaction(Organism& other) override {
        std::cout << "Turtle is hiding in its shell\n";
    }
};
