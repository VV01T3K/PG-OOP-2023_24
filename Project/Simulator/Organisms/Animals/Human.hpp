#pragma once

#include "@Animal.hpp"
class Human : public Animal {
   public:
    Human(World& world) : Animal(5, 4, world, Type::HUMAN) {}
    Human(nlohmann::json json, World& world)
        : Animal(json, world),
          ability_cooldown(json["ability_cooldown"]),
          immortality_left(json["immortality_left"]) {}
    Animal* construct() const override { return new Human(world); }

    Direction nextMove = Direction::SELF;
    bool tryUseAbility = false;

    std::string getNextMove() const {
        switch (nextMove) {
            case Direction::UP:
                return "UP";
            case Direction::DOWN:
                return "DOWN";
            case Direction::LEFT:
                return "LEFT";
            case Direction::RIGHT:
                return "RIGHT";
            default:
                return "NONE";
        }
    }

    std::string getAbiliyInfo() const {
        if (ability_cooldown > 0)
            return std::to_string(ability_cooldown) + " (cooldown)";
        if (immortality_left > 0)
            return std::to_string(immortality_left) + " (immortality)";
        return "Press SPACE to activate 🛡️immortality🛡️";
    }

   private:
    int ability_cooldown = 0;
    int immortality_left = 0;

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
        if (tryUseAbility) {
            tryUseAbility = false;
            immortality();
        }
        updateAbilities();
        if (nextMove != Direction::SELF) {
            move(nextMove);
            nextMove = Direction::SELF;
        }
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

    nlohmann::json toJson() const override {
        nlohmann::json json = Animal::toJson();
        json["ability_cooldown"] = ability_cooldown;
        json["immortality_left"] = immortality_left;
        return json;
    }

    void setNextMove(Direction direction) { nextMove = direction; }
    void switchAbility() { tryUseAbility = !tryUseAbility; }
};
