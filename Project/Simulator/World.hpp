#pragma once

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "../Utils/Display.hpp"
#include "../Utils/RandGen.hpp"
#include "Organisms/@Organism.hpp"
#include "Tile.hpp"

class Organism;
class Tile;

class World {
   private:
    size_t width;
    size_t height;
    RandGen &rng = RandGen::getInstance();
    std::vector<Organism *> organisms;  // sorted by initiative and age
    std::vector<Tile *> tiles;  // custom array of tiles (mainly for random
                                // spwaning of organisms)
    size_t time = 0;

   public:
    World(size_t width, size_t height);
    ~World();

    size_t checkTime() const;

    size_t getWidth() const;
    size_t getHeight() const;

    Tile *getTile(size_t index) const;
    Tile *getTile(size_t x, size_t y) const;
    void setTile(size_t x, size_t y, Tile *tile);

    Organism *getOrganism(size_t index) const;

    void addOrganism(Organism *organism, Tile *tile);

    void simulate();

    size_t getOrganimsCount() const;

    void spreadOrganisms(Organism *organism, size_t count);
};
