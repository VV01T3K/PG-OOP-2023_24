#pragma once

#include "../../Abilities/Immortality.hpp"
#include "@Animal.hpp"

class Immortality;
class Human : public Animal {
   public:
    Human(World& world) : Animal(5, 4, world, Type::HUMAN), immortality(5, 5) {}
    Human(nlohmann::json json, World& world)
        : Animal(json, world),
          immortality(json["ability_cooldown"], json["immortality_left"]) {}
    Animal* construct() const override { return new Human(world); }

   private:
    Direction nextMove = Direction::SELF;
    bool toggleAbility = false;
    friend class Immortality;
    Immortality immortality;

    void immortalityEffect(Organism& other) {
        Tile* newtile = tile->getRandomFreeNeighbour();
        if (newtile == nullptr) tile->getRandomNeighbour();
        if (newtile == nullptr) {
            dynamic_cast<Animal*>(&other)->undoMove();
            return;
        }
        move(newtile);
        if (tile->getOrganismCount() > 1) this->collision(*tile->getOrganism());
    }

   public:
    void action() override {
        if (toggleAbility) {
            toggleAbility = false;
            // immortality();
        }
        // updateAbilities();
        if (nextMove != Direction::SELF) {
            move(nextMove);
            nextMove = Direction::SELF;
        }
    }

    void collision(Organism& other) override {
        // if (immortality()) {
        immortalityEffect(other);
        // }
        // else
        Animal::collision(other);
    }

    bool collisionReaction(Organism& other) override {
        // if (immortality()) {
        //     immortalityEffect(other);
        //     return true;
        // } else
        return false;
    }

    nlohmann::json toJson() const override {
        nlohmann::json json = Animal::toJson();
        json["ability_cooldown"] = immortality.getCooldown();
        json["immortality_left"] = immortality.getDuration();
        return json;
    }

    void setNextMove(Direction direction) { nextMove = direction; }
    void switchAbility() { toggleAbility = !toggleAbility; }

    std::string getNextMoveSTR() const {
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
                return "Pls give me direction";
        }
    }

    Direction getNextMove() const { return nextMove; }

    std::string getAbiliyInfo() const {
        // if (immortality_left > 0)
        //     return std::to_string(immortality_left) + " turns left";
        // if (ability_cooldown > 0)
        //     return std::to_string(ability_cooldown) + " turns cooldown";
        // if (toggleAbility) return "Using next turn";
        return "Ready to use";
    }
};
