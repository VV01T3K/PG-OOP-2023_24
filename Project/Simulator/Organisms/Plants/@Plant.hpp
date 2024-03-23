#pragma once

#include <iostream>
#include <random>

#include "../../World.hpp"
#include "../@Organism.hpp"

class Plant : public Organism {
   public:
    Plant(int power, World& world) : Organism(power, 0, world) {}
    virtual void action() override {
        if (rng.roll(0, 100) < 5) {
            Tile* newtile = tile->getRandomFreeNeighbour();
            if (newtile == nullptr) return;
            Plant* newPlant = construct();
            newPlant->skipTurn();
            world.addOrganism(newPlant, newtile);
            // this->setSpreadCooldown(5);
            // newPlant->setSpreadCooldown(5);
        }
    }
    virtual void collision(Organism& other) override {}
    virtual void collision(const Organism& other) override {}

    void setSpreadCooldown(int cooldown = 5) {
        reproduction_cooldown = cooldown;
    }
    int getSpreadCooldown() const { return reproduction_cooldown; }

    virtual void draw() = 0;
    virtual Plant* construct() const = 0;
};