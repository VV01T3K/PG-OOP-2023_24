#pragma once

#include <nlohmann/json.hpp>

#include "../../World.hpp"
#include "../@Organism.hpp"

class Animal : public Organism {
   protected:
    Tile* oldTile = nullptr;

    void move(Tile* newtile) {
        if (newtile == nullptr) return;
        oldTile = tile;
        tile = newtile;
        tile->placeOrganism(this);
        oldTile->removeOrganism(this);
    }
    void move(Direction direction) { move(tile->getNeighbour(direction)); }

   public:
    Animal(int power, int initiative, World& world, Type type)
        : Organism(type, power, initiative, world) {}
    Animal(nlohmann::json json, World& world) : Organism(json, world) {
        int32_t index = json["old_tile_index"];
        oldTile = index == -1 ? nullptr : world.getTile(index);
    }
    virtual void action() override { move(tile->getRandomNeighbour()); }
    virtual void collision(Organism& other) override {
        if (other.collisionReaction(*this)) return;
        if (typeid(*this) == typeid(other)) {
            this->undoMove();
            if (!GlobalSettings::AI_REPRODUCE) return;
            other.skipTurn();
            if (reproduction_cooldown > 0) return;
            Tile* newtile = other.getTile()->getRandomFreeNeighbour();
            if (newtile == nullptr) return;
            Animal* newAnimal = construct();
            newAnimal->skipTurn();
            this->setBreedCooldown(5);
            other.setBreedCooldown(5);
            newAnimal->setBreedCooldown(10);
            world.addOrganism(newAnimal, newtile);

            world.addLog(this->getSymbol() + " and " + other.getSymbol() +
                         " bred a new " + newAnimal->getSymbol() + "!");

        } else if (power > other.getPower()) {
            other.Die();
            world.addLog(this->getSymbol() + " killed " + other.getSymbol() +
                         "!");
        } else {
            this->Die();
            world.addLog(this->getSymbol() + " was killed by " +
                         other.getSymbol() + "!");
        }
    }
    virtual bool collisionReaction(Organism& other) override { return false; }

    void setBreedCooldown(int cooldown = 5) {
        reproduction_cooldown = cooldown;
    }
    int getBreedCooldown() const { return reproduction_cooldown; }

    virtual void undoMove() {
        if (oldTile == nullptr) return;
        oldTile->placeOrganism(this);
        tile->removeOrganism(this);
        tile = oldTile;
        oldTile = nullptr;
    }
    virtual Animal* construct() const = 0;

    virtual nlohmann::json toJson() const override {
        nlohmann::json json = Organism::toJson();
        int32_t index = oldTile == nullptr ? -1 : oldTile->index;
        json["old_tile_index"] = index;
        return json;
    }
};