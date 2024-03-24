#pragma once

#include <nlohmann/json.hpp>

#include "../GlobalSettings.hpp"

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

   public:
    enum class Type : u_int8_t {
        ANTELOPE,
        CYBER_SHEEP,
        FOX,
        HUMAN,
        SHEEP,
        TURTLE,
        WOLF,
        GRASS,
        GUARANA,
        MILKWEED,
        SOSNOWSKY_HOGWEED,
        WOLF_BERRIES
    };
    const Type type;
    Organism(Type type, int power, int initiative, World &world);

    Tile *getTile() const;
    void setTile(Tile *tile);

    void Age();
    void setBreedCooldown(size_t turns = 5) { reproduction_cooldown = turns; }
    void Die();
    bool isDead() const;
    bool isAlive() const;
    void skipTurn();
    void unskipTurn();
    bool isSkipped() const;

    int getPower() const;
    int getInitiative() const;
    int getAge() const;
    void setPower(int power);
    void setInitiative(int initiative);
    ~Organism();
    virtual void action() = 0;
    virtual void collision(Organism &other) = 0;
    virtual bool collisionReaction(Organism &other) = 0;
    virtual void draw() = 0;
    virtual Organism *construct() const = 0;
    virtual nlohmann::json toJson() const;
    Organism(nlohmann::json j, World &world);
};