#pragma once

#include <iostream>
#include <random>
#include <string>

#include "../@Organism.hpp"

class Plant : public Organism {
   public:
    Plant(int power, World& world, Type type)
        : Organism(type, power, 0, world) {}
    Plant(nlohmann::json json, World& world) : Organism(json, world) {}
    virtual void action() override {
        if (!GlobalSettings::AI_REPRODUCE) return;
        if (RNG::roll(0, 100) < 5) {
            Tile* newtile = tile->getRandomFreeNeighbour();
            if (newtile == nullptr) return;
            Plant* newPlant = construct();
            newPlant->skipTurn();
            world.addOrganism(newPlant, newtile);
            // this->setSpreadCooldown(5);
            // newPlant->setSpreadCooldown(5);

            world.addLog(getSymbol() + " is spreading!!");
        }
    }
    virtual void collision(Organism& other) override {}
    virtual bool collisionReaction(Organism& other) override { return false; }

    void setSpreadCooldown(int cooldown = 5) {
        reproduction_cooldown = cooldown;
    }
    int getSpreadCooldown() const { return reproduction_cooldown; }

    virtual Plant* construct() const = 0;
};