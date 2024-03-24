#pragma once

#include <array>
#include <vector>

#include "../Utils/RandGen.hpp"
#include "Organisms/@Organism.hpp"

class Organism;

enum class Direction : u_int8_t { UP, DOWN, RIGHT, LEFT, SELF };
class Tile {
   private:
    std::array<Tile *, 4> directions;
    std::vector<Organism *> organisms;

   public:
    const size_t index;

    Tile(size_t index);
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

    size_t getOrganismCount() const;

    size_t getDistanceTo(const Tile *tile, size_t width) const;
};
