#pragma once

#include <array>
#include <vector>

#include "../Utils/RandGen.hpp"
#include "Organisms/Organism.hpp"

class Organism;

enum class Direction : size_t { UP, DOWN, RIGHT, LEFT, SELF };
class Tile {
   private:
    std::array<Tile *, 4> directions;

   public:
    std::vector<Organism *> organisms;
    void print() {
        if (organisms.empty()) {
            std::cout << "Empty";
        } else {
            for (auto &organism : organisms) {
                if (organism != nullptr) cout << "sheep ";
            }
        }
    }

    Tile() {
        directions.fill(nullptr);
        organisms.reserve(1);
    }
    ~Tile(){};

    void clear() { organisms.clear(); }

    void setLink(Direction direction, Tile *tile) {
        directions[static_cast<size_t>(direction)] = tile;
    }

    Organism *getOrganism() const { return organisms[0]; }
    void placeOrganism(Organism *organism) { organisms.push_back(organism); }
    void removeOrganism(Organism *organism) {
        organisms.erase(
            std::remove(organisms.begin(), organisms.end(), organism),
            organisms.end());
    }

    Tile &operator[](Direction direction) {
        if (direction == Direction::SELF) return *this;
        return *directions[static_cast<size_t>(direction)];
    }
    Tile *getRandomFreeNeighbour() const {
        std::vector<Tile *> neighbours;
        for (auto &direction : directions) {
            if (direction != nullptr && direction->isFree()) {
                neighbours.push_back(direction);
            }
        }
        if (neighbours.empty()) return nullptr;
        return neighbours[RandGen::getInstance().roll(0,
                                                      neighbours.size() - 1)];
    }

    Tile *getNeighbour(Direction direction) const {
        return directions[static_cast<size_t>(direction)];
    }
    Tile *getRandomNeighbour() const {
        std::vector<Tile *> neighbours;
        for (auto &direction : directions) {
            if (direction != nullptr) {
                neighbours.push_back(direction);
            }
        }
        if (neighbours.empty()) return nullptr;
        return neighbours[RandGen::getInstance().roll(0,
                                                      neighbours.size() - 1)];
    }
    Direction getRandomDirection() const {
        std::vector<Direction> directions;
        for (auto &direction : this->directions) {
            if (direction != nullptr) {
                directions.push_back(
                    static_cast<Direction>(&direction - &this->directions[0]));
            }
        }
        if (directions.empty()) return Direction::SELF;
        return directions[RandGen::getInstance().roll(0,
                                                      directions.size() - 1)];
    }

    bool isFree() const { return organisms.empty(); }
};
