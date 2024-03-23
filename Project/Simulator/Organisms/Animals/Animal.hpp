#pragma once

#include <iostream>
#include <random>

#include "../../World.hpp"
#include "../Organism.hpp"

class Animal : public Organism {
   protected:
    Tile* oldTile = nullptr;

    void move(Tile* newtile) {
        if (newtile == nullptr) return;
        std::cout << "Moving";
        oldTile = tile;
        tile = newtile;
        tile->placeOrganism(this);
        oldTile->removeOrganism(this);
    }
    void move(Direction direction) { move(tile->getNeighbour(direction)); }

   public:
    Animal(int power, int initiative, World& world)
        : Organism(power, initiative, world) {}
    virtual void action() override { move(tile->getRandomNeighbour()); }
    virtual void collision(Organism& other) override {
        if (typeid(*this) == typeid(other) && breed_cooldown == 0) {
            this->undoMove();
            Tile* newtile = other.getTile()->getRandomFreeNeighbour();
            if (newtile == nullptr) return;
            other.collision(static_cast<const Organism&>(*this));
            Animal* newAnimal = construct();
            newAnimal->skipTurn();
            world.addOrganism(newAnimal, newtile);
            this->setBreedCooldown(5);
            other.setBreedCooldown(5);
            newAnimal->setBreedCooldown(10);

        } else
            undoMove();
    }
    virtual void collision(const Organism& other) override { this->skipTurn(); }

    void setBreedCooldown(int cooldown = 5) { breed_cooldown = cooldown; }
    int getBreedCooldown() const { return breed_cooldown; }

    virtual void undoMove() {
        if (oldTile == nullptr) return;
        oldTile->placeOrganism(this);
        tile->removeOrganism(this);
        tile = oldTile;
        oldTile = nullptr;
    }
    virtual void draw() = 0;
    virtual Animal* construct() const = 0;
};