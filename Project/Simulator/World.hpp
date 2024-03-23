#pragma once

#include <algorithm>
#include <vector>

// #include "../Utils/Controler.hpp"
// #include "../Utils/Display.hpp"
#include "Organisms/Organism.hpp"
#include "Position.hpp"

class World {
   private:
    int width;
    int height;
    std::vector<Organism *> organisms;
    // Display &display;
    // Controler &controler;

   public:
    World(int width, int height) : width(width), height(height) {
        std::cout << "World constructor" << std::endl;
    };
    ~World() {
        for (auto organism : organisms) {
            delete organism;
        }
    }

    int getWidth() { return width; }
    int getHeight() { return height; }

    void setWidth(int width) { this->width = width; }
    void setHeight(int height) { this->height = height; }

    void addOrganism(Organism *organism) { organisms.push_back(organism); }
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

    void simulateOneRound() {
        simulate();
        // display.draw(this);
        // controler.waitForInput();
    }

    void draw() {
        std::cout << "World size: " << width << "x" << height << std::endl;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (isOccupied(Position(x, y))) {
                    std::cout << "1 ";
                } else {
                    std::cout << "0 ";
                }
            }
            std::cout << std::endl;
        }
    }
};
