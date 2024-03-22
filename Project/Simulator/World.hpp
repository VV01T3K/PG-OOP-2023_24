#pragma once

#include <algorithm>
#include <vector>

#include "../Utils/Controler.hpp"
#include "../Utils/Display.hpp"
#include "Organisms/Organism.hpp"
#include "Position.hpp"

class World {
   private:
    std::vector<Organism *> organisms;
    Display display;
    Controler controler;
    int width;
    int height;

   public:
    World() {}
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
        for (auto organism : organisms) {
            organism->action();
        }
    }
    void collisions() {
        for (auto organism1 : organisms) {
            for (auto organism2 : organisms) {
                if (organism1 != organism2 &&
                    organism1->getPosition() == organism2->getPosition()) {
                    organism1->collision(*organism2);
                }
            }
        }
    }

    bool isOccupied(Position position) {
        for (auto organism : organisms) {
            if (organism->getPosition() == position) {
                return true;
            }
        }
        return false;
    }

    void simulateOneRound() {
        simulate();
        collisions();
        display.draw(this);
        controler.waitForInput();
    }
};
