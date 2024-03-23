#pragma once

#include <iostream>

#include "../Position.hpp"
#include "../World.hpp"

class World;  // Forward declaration of World

class Organism {
   protected:
    int power;
    int initiative;
    int age;
    bool alive;
    Position position;
    World &world;

    enum class Direction : uint8_t { UP, DOWN, LEFT, RIGHT };

   public:
    Organism(int power, int initiative, int x, int y, World &world)
        : power(power),
          initiative(initiative),
          age(0),
          alive(true),
          position(x, y),
          world(world) {}
    Organism(int power, int initiative, Position position, World &world)
        : power(power),
          initiative(initiative),
          age(0),
          alive(true),
          position(position),
          world(world) {}

    int getPower() const { return power; }
    int getInitiative() const { return initiative; }
    int getAge() const { return age; }
    bool isAlive() const { return alive; }
    int getX() const { return position.x; }
    int getY() const { return position.y; }
    void setPower(int power) { this->power = power; }
    void setInitiative(int initiative) { this->initiative = initiative; }
    void setAge(int age) { this->age = age; }
    void setAlive(bool alive) { this->alive = alive; }
    void setPosition(int x, int y) {
        position.x = x;
        position.y = y;
    }
    Position getPosition() const { return position; }
    void setPosition(Position position) { this->position = position; }
    void skipTurn() {}
    virtual ~Organism() { std::cout << "Organism destructor" << std::endl; }
    virtual void action() = 0;
    virtual void collision(Organism &other) = 0;
    virtual void draw() = 0;
    virtual void die() { alive = false; }

    virtual bool operator==(const Organism &other) const {
        return power == other.power && initiative == other.initiative &&
               position == other.position;
    }
    virtual bool operator!=(const Organism &other) const {
        return !(*this == other);
    }
};