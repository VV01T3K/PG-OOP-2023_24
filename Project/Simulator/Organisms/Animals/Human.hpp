#pragma once

#include "@Animal.hpp"
class Human : public Animal {
   public:
    Human(World& world) : Animal(5, 4, world, Type::HUMAN) {}
    void draw() override { std::cout << "🧑"; }
    Animal* construct() const override { return new Human(world); }

    int ability_cooldown = 0;
    int immortality_left = 0;

   private:
    bool immortality() {
        if (immortality_left > 0) return true;
        if (ability_cooldown > 0) return false;
        ability_cooldown = 5;
        immortality_left = 5;
        return true;
    }

    void useImmortality(Organism& other) {
        Tile* newtile = tile->getRandomFreeNeighbour();
        if (newtile == nullptr) tile->getRandomNeighbour();
        if (newtile == nullptr) {
            dynamic_cast<Animal*>(&other)->undoMove();
            return;
        }
        move(newtile);
        if (tile->getOrganismCount() > 1) this->collision(*tile->getOrganism());
    }

    void updateAbilities() {
        if (immortality_left > 0) {
            immortality_left--;
        } else if (ability_cooldown > 0) {
            ability_cooldown--;
        }
    }

   public:
    void action() override {
        immortality();
        updateAbilities();
        Animal::action();
    }

    void collision(Organism& other) override {
        if (immortality()) {
            useImmortality(other);
        } else
            Animal::collision(other);
    }

    bool collisionReaction(Organism& other) override {
        if (immortality()) {
            useImmortality(other);
            return true;
        } else
            return false;
    }
};
