#pragma once

#include "@Animal.hpp"
class Turtle : public Animal {
   public:
    Turtle(World& world) : Animal(2, 1, world) {}
    void draw() override { std::cout << "🐢"; }
    Animal* construct() const override { return new Turtle(world); }

    void action() override {
        // 75% chance to skip turn
        if (rng.roll(0, 100) < 75) return;
        Animal::action();
    };

    bool collisionReaction(Organism& other) override {
        if (typeid(other) == typeid(Turtle)) return false;
        if (other.getPower() < 5) {
            dynamic_cast<Animal*>(&other)->undoMove();
            std::cout << "Turtle blocked the attack!\n";
            std::cin.get();
            return true;
        }
        return false;
    }
};
