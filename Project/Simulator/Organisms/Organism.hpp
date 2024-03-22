#pragma once

#include "../Position.hpp"
#include "../World.hpp"

class Organism {
   protected:
    int power;
    int initiative;
    Position position;
    World &world;

   public:
    Organism(int power, int initiative, int x, int y, World &world)
        : power(power), initiative(initiative), position(x, y), world(world) {}
    int getPower() const { return power; }
    int getInitiative() const { return initiative; }
    int getX() const { return position.x; }
    int getY() const { return position.y; }
    void setPower(int power) { this->power = power; }
    void setInitiative(int initiative) { this->initiative = initiative; }
    void setPosition(int x, int y) {
        position.x = x;
        position.y = y;
    }
    Position getPosition() const { return position; }
    void setPosition(Position position) { this->position = position; }
    virtual ~Organism() {}
    virtual void action() = 0;
    virtual void collision(Organism &organism) = 0;
    virtual void draw() = 0;
};