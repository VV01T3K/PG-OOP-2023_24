#pragma once

#include <algorithm>
#include <vector>

#include "Organisms/Organism.hpp"
#include "Utils/Controler.hpp"
#include "Utils/Display.hpp"
#include "Utils/Position.hpp"

class World {
   private:
    std::vector<Organism *> organisms;
    Display display;
    Controler controler;

   public:
    World() {}
    ~World() {
        for (auto organism : organisms) {
            delete organism;
        }
    }
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
                    organism1->getX() == organism2->getX() &&
                    organism1->getY() == organism2->getY()) {
                    organism1->collision(*organism2);
                }
            }
        }
    }

    void simulateOneRound() {
        simulate();
        collisions();
        display.draw(this);
        controler.waitForInput();
    }
};
