#include "Display.hpp"

Display::Display(World &world) : world(world) {}
Display::~Display(){};

void Display::printOrganisms() const {
    for (size_t y = 0; y < world.getHeight(); y++) {
        for (size_t x = 0; x < world.getWidth(); x++) {
            Tile *tile = world.getTile(y * world.getWidth() + x);
            if (tile->getOrganism() != nullptr) {
                tile->getOrganism()->draw();
                std::cout << " ";
            } else {
                std::cout << "☐ ";
            }
        }
        std::cout << std::endl;
    }
}