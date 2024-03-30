#pragma once

#include "@Animal.hpp"
class Turtle : public Animal {
   public:
    Turtle(World& world) : Animal(2, 1, world, Type::TURTLE) {}
    Turtle(nlohmann::json json, World& world) : Animal(json, world) {}
    Animal* construct() const override { return new Turtle(world); }

    void action() override {
        // 75% chance to skip turn
        if (RNG::roll(0, 100) < 75) return;
        Animal::action();
    };

    bool collisionReaction(Organism& other) override {
        if (typeid(other) == typeid(Turtle)) return false;
        if (other.getPower() < 5) {
            dynamic_cast<Animal*>(&other)->undoMove();
            world.addLog(other.getSymbol() + " tried to attack " + getSymbol() +
                         " but failed!");
            return true;
        }
        return false;
    }
};
