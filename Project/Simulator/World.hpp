#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

#include "../Utils/Display.hpp"
#include "../Utils/RNG.hpp"
#include "Organisms/@Organism.hpp"
#include "Tile.hpp"

class Organism;
class Tile;

class World {
   private:
    size_t width;
    size_t height;
    size_t time = 0;
    std::vector<Organism *> organisms;  // sorted by initiative and age
    std::vector<Tile *> tiles;
    std::vector<std::string> logs;

   public:
    World() = default;
    World(size_t width, size_t height);
    ~World();

    void addLog(std::string log);
    const std::vector<std::string> &getLogs() const;
    void clearLogs();

    void setWorld(size_t width, size_t height, size_t time);

    void createBoard(size_t width, size_t height);

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

    void clearOrganisms();
    void clearTiles();

    void linkOrganismsWithTiles();
    void setOrganisms(std::vector<Organism *> organisms);
    std::vector<Organism *> getOrganisms() const;
};