#pragma once

#include <array>

#include "Organisms/Organism.hpp"
#include "Position.hpp"

enum class Direction : uint8_t { NORTH, EAST, SOUTH, WEST, SELF };
class Tile {
   private:
    Position position;
    Organism *organism;
    std::array<Tile *, 4> directions;

   public:
    bool test = false;

    Tile() : organism(nullptr) { directions.fill(nullptr); }

    Tile(Position position) : Tile() { this->position = position; }
    Tile(int x, int y) : Tile() { position = Position(x, y); }

    ~Tile(){};

    void setLink(Direction direction, Tile *tile) {
        directions[static_cast<uint8_t>(direction)] = tile;
    }

    Position getPosition() { return position; }
    void setPosition(Position position) { this->position = position; }
    Organism *getOrganism() { return organism; }
    void setOrganism(Organism *organism) { this->organism = organism; }
    Tile &operator[](Direction direction) {
        if (direction == Direction::SELF) return *this;
        return *directions[static_cast<uint8_t>(direction)];
    }
    Tile *getRandomNeighbour() {
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
};
