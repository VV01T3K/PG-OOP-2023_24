#pragma once

#include <array>
#include <vector>

#include "../Utils/RandGen.hpp"
#include "Organisms/@Organism.hpp"

enum class Direction : size_t { UP, DOWN, RIGHT, LEFT, SELF };
class Tile {
   private:
    std::array<Tile *, 4> directions;

   public:
    std::vector<Organism *> organisms;

    Tile();
    ~Tile();

    void clear();

    void setLink(Direction direction, Tile *tile);

    Organism *getOrganism() const;
    void placeOrganism(Organism *organism);
    void removeOrganism(Organism *organism);

    Tile *getRandomFreeNeighbour() const;

    Tile *getNeighbour(Direction direction) const;
    Tile *getRandomNeighbour() const;
    Direction getRandomDirection() const;

    std::vector<Tile *> getNeighbours() const;
    std::vector<Tile *> getOccupiedNeighbours() const;

    bool isFree() const;
};