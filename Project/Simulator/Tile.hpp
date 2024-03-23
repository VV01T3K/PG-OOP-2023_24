#pragma once

#include "Organisms/Organism.hpp"
#include "Position.hpp"

class Tile {
   private:
    Position position;
    Organism *organism;
    Tile *north;
    Tile *east;
    Tile *south;
    Tile *west;

   public:
    bool test = false;
    enum class Direction : uint8_t { SELF, NORTH, EAST, SOUTH, WEST };

    Tile()
        : north(nullptr),
          east(nullptr),
          south(nullptr),
          west(nullptr),
          organism(nullptr) {}

    Tile(Position position) : Tile() { this->position = position; }
    Tile(int x, int y) : Tile() { position = Position(x, y); }

    ~Tile(){};

    void setLink(Direction direction, Tile *tile) {
        switch (direction) {
            case Direction::NORTH:
                north = tile;
                break;
            case Direction::EAST:
                east = tile;
                break;
            case Direction::SOUTH:
                south = tile;
                break;
            case Direction::WEST:
                west = tile;
                break;
        }
    }

    Position getPosition() { return position; }
    void setPosition(Position position) { this->position = position; }
    Organism *getOrganism() { return organism; }
    void setOrganism(Organism *organism) { this->organism = organism; }
    Tile operator[](Direction direction) {
        switch (direction) {
            case Direction::SELF:
                return *this;
            case Direction::NORTH:
                return *north;
            case Direction::EAST:
                return *east;
            case Direction::SOUTH:
                return *south;
            case Direction::WEST:
                return *west;
        }
    }
    Tile *getRandomNeighbour() {
        std::vector<Tile *> neighbours;
        if (north != nullptr) neighbours.push_back(north);
        if (east != nullptr) neighbours.push_back(east);
        if (south != nullptr) neighbours.push_back(south);
        if (west != nullptr) neighbours.push_back(west);
        if (neighbours.empty()) return nullptr;
        return neighbours[RandGen::getInstance().roll(0,
                                                      neighbours.size() - 1)];
    }
};
