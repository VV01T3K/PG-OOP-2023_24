#pragma once

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "../Utils/RandGen.hpp"
#include "Organisms/Organism.hpp"
#include "Tile.hpp"

class World {
   private:
    size_t width;
    size_t height;
    RandGen &rng = RandGen::getInstance();
    std::vector<Organism *> organisms;  // sorted by initiative and age
    std::vector<Tile *> tiles;  // custom array of tiles (mainly for random
                                // spwaning of organisms)

   public:
    World(size_t width, size_t height) : width(width), height(height) {
        tiles.reserve(width * height);
        for (size_t y = 0; y < height; y++) {
            for (size_t x = 0; x < width; x++) {
                tiles.push_back(new Tile());
            }
        }
        for (size_t y = 0; y < height; y++) {
            for (size_t x = 0; x < width; x++) {
                Tile *tile = tiles[y * width + x];
                if (y > 0) {
                    tile->setLink(Direction::UP, tiles[(y - 1) * width + x]);
                }
                if (x < width - 1) {
                    tile->setLink(Direction::RIGHT, tiles[y * width + x + 1]);
                }
                if (y < height - 1) {
                    tile->setLink(Direction::DOWN, tiles[(y + 1) * width + x]);
                }
                if (x > 0) {
                    tile->setLink(Direction::LEFT, tiles[y * width + x - 1]);
                }
            }
        }
    };
    ~World() {
        for (auto organism : organisms) {
            delete organism;
        }
        for (auto tile : tiles) {
            delete tile;
        }
    }

    size_t getWidth() const { return width; }
    size_t getHeight() const { return height; }

    Tile *getTile(size_t index) const { return tiles[index]; }
    Tile *getTile(size_t x, size_t y) const { return tiles[y * width + x]; }
    void setTile(size_t x, size_t y, Tile *tile) {
        tiles[y * width + x] = tile;
    }

    Organism *getOrganism(size_t index) const { return organisms[index]; }

    void addOrganism(Organism *organism, Tile *tile) {
        organisms.push_back(organism);
        organism->setTile(tile);
        tile->placeOrganism(organism);
    }

    void simulate() {
        for (auto organism : organisms) {
            if (organism->isSkipped()) {
                organism->unskipTurn();
                continue;
            }
            if (organism->isDead()) return;
            organism->action();
            for (auto other : organisms) {
                if (organism != other &&
                    organism->getTile() == other->getTile()) {
                    organism->collision(*other);
                }
            }
        }
        for (auto organism : organisms) {
            organism->Age();
            if (organism->isDead()) {
                Tile *tile = organism->getTile();
                tile->clear();
                organisms.erase(
                    std::remove(organisms.begin(), organisms.end(), organism),
                    organisms.end());
                delete organism;
            }
        }
    }

    void printOrganisms() {
        std::cout << "World size: " << width << "x" << height << std::endl;
        for (size_t y = 0; y < height; y++) {
            for (size_t x = 0; x < width; x++) {
                Tile *tile = tiles[y * width + x];
                if (!tile->isFree()) {
                    tile->getOrganism()->draw();
                    std::cout << " ";
                    if (tile->organisms.size() > 1) {
                        std::cout << "+";
                    } else {
                        std::cout << "";
                    }
                } else {
                    std::cout << "☐ ";
                }
            }
            std::cout << std::endl;
        }
    }

    size_t getOrganimsCount() const { return organisms.size(); }
};
