#pragma once

#include "@Animal.hpp"
class Antelope : public Animal {
   public:
    Antelope(World& world) : Animal(4, 4, world, Type::ANTELOPE) {}
    Antelope(nlohmann::json json, World& world) : Animal(json, world) {}
    Animal* construct() const override { return new Antelope(world); }

    void action() override {
        Animal::action();
        if (tile->getOrganismCount() > 1) return;
        std::vector<Tile*> neighbours = tile->getNeighbours();
        neighbours.erase(
            std::remove(neighbours.begin(), neighbours.end(), oldTile),
            neighbours.end());
        if (neighbours.empty()) return;
        Tile* newTile = neighbours[RNG::roll(0, neighbours.size() - 1)];
        move(newTile);
    }

    void collision(Organism& other) override {
        if (typeid(other) == typeid(Antelope))
            Animal::collision(other);
        else if (RNG::roll(0, 100) < 50) {
            Tile* newTile = tile->getRandomFreeNeighbour();
            if (newTile == nullptr) {
                Animal::collision(other);
                return;
            }
            world.addLog(getSymbol() + " escaped from " + other.getSymbol() +
                         "!");
            move(newTile);
        } else
            Animal::collision(other);
    }

    bool collisionReaction(Organism& other) override {
        if (RNG::roll(0, 100) < 50) {
            Tile* newTile = tile->getRandomFreeNeighbour();
            if (newTile == nullptr) return false;
            world.addLog(getSymbol() + " escaped from " + other.getSymbol() +
                         "!");
            move(newTile);
            return true;
        }
        return false;
    }
};
