#include "CyberSheep.hpp"

size_t CyberSheep::getDistanceTo(size_t index){

};

size_t CyberSheep::seekClosestSosnowskyHogweed() {
    size_t index = 0;
    for (size_t i = 0; i < world.getOrganimsCount(); i++) {
        if (typeid(*world.getOrganism(i)) == typeid(SosnowskyHogweed)) {
        }
    }
    return index;
};

Tile* CyberSheep::nextTileToSosnowskyHogweed(size_t index){};