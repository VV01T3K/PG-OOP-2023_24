#include "Display.hpp"

#include <iostream>

#include "../Simulator/Organisms/Animals/Human.hpp"

using namespace std;

Display::Display(World &world) : world(world) {}
Display::~Display(){};

void Display::update() const {
    cout << "Time: " << world.checkTime() << '\n';
    cout << "World size: " << world.getWidth() << "x" << world.getHeight()
         << '\n';
    for (size_t y = 0; y < world.getHeight(); y++) {
        for (size_t x = 0; x < world.getWidth(); x++) {
            Tile *tile = world.getTile(x, y);
            if (!tile->isFree()) {
                tile->getOrganism()->draw();
            } else {
                cout << "🔳";
            }
        }
        cout << '\n';
    }
    cout << "Entities: " << world.getOrganimsCount() << '\n';
}