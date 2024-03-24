#pragma once

#include <iostream>

#include "../Tile.hpp"
#include "../World.hpp"

class World;
class Tile;

class Organism {
   protected:
    int power;
    int initiative;
    u_int32_t age = 0;
    bool alive = true;
    int reproduction_cooldown;
    bool skip = false;
    Tile *tile = nullptr;
    World &world;
    RandGen &rng = RandGen::getInstance();

   public:
    Organism(int power, int initiative, World &world)
        : power(power), initiative(initiative), world(world) {}

    Tile *getTile() const { return tile; }
    void setTile(Tile *tile) { this->tile = tile; }

    void Age() {
        if (reproduction_cooldown > 0) reproduction_cooldown--;
        age++;
    }
    void setBreedCooldown(size_t turns = 5) { reproduction_cooldown = turns; }
    void Die() { alive = false; }
    bool isDead() { return !alive; }
    bool isAlive() const { return alive; }
    void skipTurn() { skip = true; }
    void unskipTurn() { skip = false; }
    bool isSkipped() { return skip; }

    int getPower() const { return power; }
    int getInitiative() const { return initiative; }
    int getAge() const { return age; }
    void setPower(int power) { this->power = power; }
    void setInitiative(int initiative) { this->initiative = initiative; }
    ~Organism() {}
    virtual void action() = 0;
    virtual void collision(Organism &other) = 0;
    virtual void collisionReaction(Organism &other) = 0;
    virtual void draw() = 0;
    virtual Organism *construct() const = 0;
};