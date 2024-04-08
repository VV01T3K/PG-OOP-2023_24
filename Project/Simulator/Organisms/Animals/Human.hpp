#pragma once

#include "../../Abilities/Immortality.hpp"
#include "@Animal.hpp"

class Immortality;
class Human : public Animal {
   private:
    Direction nextMove = Direction::SELF;
    friend class Immortality;
    Immortality immortality;

   public:
    Human(World& world) : Animal(5, 4, world, Type::HUMAN), immortality(5, 5) {}
    Human(nlohmann::json json, World& world)
        : Animal(json, world),
          immortality(json["ability_cooldown"], json["immortality_left"], 5,
                      5) {
        if (json["immortality_left"] > 0 || json["ability_cooldown"] == 0) {
            immortality.use();
        }
    }
    Animal* construct() const override { return new Human(world); }

    void action() override {
        if (GlobalSettings::HUMAN_AI) {
            immortality.use();
            immortality.update();
            Animal::action();
            return;
        }
        if (nextMove == Direction::SELF) return;
        if (immortality.checkToggle()) {
            immortality.use();
            immortality.flipToggle();
        }
        immortality.update();
        move(nextMove);
        nextMove = Direction::SELF;
    }

    void collision(Organism& other) override {
        if (immortality.isActive()) {
            immortality.effect(*this, other);
            return;
        } else
            Animal::collision(other);
    }

    bool collisionReaction(Organism& other) override {
        if (immortality.isActive()) {
            immortality.effect(*this, other);
            return true;
        } else
            return false;
    }

    nlohmann::json toJson() const override {
        nlohmann::json json = Animal::toJson();
        json["ability_cooldown"] = immortality.getCooldown();
        json["immortality_left"] = immortality.getDuration();
        return json;
    }

    void setNextMove(Direction direction) { nextMove = direction; }
    void toggleImortality() {
        if (immortality.isReady() && !immortality.isActive())
            immortality.flipToggle();
    }

    std::string getNextMoveSTR() const {
        if (GlobalSettings::HUMAN_AI) return "AI controlled";
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
        if (immortality.isActive())
            return std::to_string(immortality.getDuration()) + " turns left";
        if (!immortality.isReady())
            return std::to_string(immortality.getCooldown()) +
                   " turns of cooldown";
        if (immortality.checkToggle()) return "Using next turn";
        return "Ready to use";
    }
};
