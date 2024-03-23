#pragma once

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "../Utils/RandGen.hpp"
#include "Organisms/Organism.hpp"
#include "Position.hpp"
#include "Tile.hpp"

class World {
   private:
    int width;
    int height;
    std::vector<Organism *> organisms;  // sorted by initiative and age
    std::vector<Tile *> tiles;  // custom array of tiles (mainly for random
                                // spwaning of organisms)

   public:
    RandGen &rng = RandGen::getInstance();

    Tile &getTile(Position position) {
        return *tiles[position.y * width + position.x];
    }
    Tile &getTile(int x, int y) { return *tiles[y * width + x]; }

    World(int width, int height) : width(width), height(height) {
        tiles.reserve(width * height);
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                tiles.push_back(new Tile(x, y));
            }
        }
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                Tile *tile = tiles[y * width + x];
                if (y > 0) {
                    tile->setLink(Direction::NORTH, tiles[(y - 1) * width + x]);
                }
                if (x < width - 1) {
                    tile->setLink(Direction::EAST, tiles[y * width + x + 1]);
                }
                if (y < height - 1) {
                    tile->setLink(Direction::SOUTH, tiles[(y + 1) * width + x]);
                }
                if (x > 0) {
                    tile->setLink(Direction::WEST, tiles[y * width + x - 1]);
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

    int getWidth() { return width; }
    int getHeight() { return height; }

    void setWidth(int width) { this->width = width; }
    void setHeight(int height) { this->height = height; }

    void addOrganism(Organism *organism) {
        organisms.push_back(organism);
        getTile(organism->getPosition()).setOrganism(organism);
    }
    void removeOrganism(Organism *organism) {
        organisms.erase(
            std::remove(organisms.begin(), organisms.end(), organism),
            organisms.end());
        delete organism;
    }

    void simulate() {
        const auto compare = [](const auto &a, const auto &b) {
            if (a->getInitiative() == b->getInitiative()) {
                return a->getAge() > b->getAge();
            }
            return a->getInitiative() > b->getInitiative();
        };
        std::sort(organisms.begin(), organisms.end(), compare);
        for (auto organism : organisms) {
            if (!organism->isAlive()) continue;
            organism->action();
            for (auto other : organisms) {
                if (!other->isAlive() || organism == other) continue;
                if (organism->getPosition() == other->getPosition()) {
                    organism->collision(*other);
                }
            }
            organism->setAge(organism->getAge() + 1);
        }
        organisms.erase(
            // remove_if to shift all dead organisms to the end of the vector
            std::remove_if(
                organisms.begin(), organisms.end(),
                // Lambda function to check if an organism is dead
                [](const auto &organism) { return !organism->isAlive(); }),
            organisms.end());
    }

    bool isOccupied(Position position) {
        for (auto organism : organisms) {
            if (organism->getPosition() == position) {
                return true;
            }
        }
        return false;
    }

    Organism *getOrganismAt(Position position) {
        for (auto organism : organisms) {
            if (organism->getPosition() == position) {
                return organism;
            }
        }
        return nullptr;
    }

    void simulateOneRound() { simulate(); }

    void printTiles() {
        std::cout << "World size: " << width << "x" << height << std::endl;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                Tile *tile = tiles[y * width + x];
                if (tile->getOrganism() != nullptr) {
                    std::cout << "1 ";
                } else {
                    std::cout << "0 ";
                }
            }
            std::cout << std::endl;
        }
    }

    void printOrganisms() {
        for (auto organism : organisms) {
            std::cout << "Organism at " << organism->getPosition() << " is "
                      << (organism->isAlive() ? "alive" : "dead") << std::endl;
        }
    }
};
