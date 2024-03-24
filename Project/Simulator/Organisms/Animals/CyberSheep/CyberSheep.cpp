#include "CyberSheep.hpp"

size_t CyberSheep::getDistanceTo(Tile* tile) {
    return tile->index - (world.getWidth() * (tile->index / world.getWidth()));
};

size_t CyberSheep::seekClosestSosnowskyHogweed() {
    size_t index = -1;
    size_t min_distance = -1;
    for (size_t i = 0; i < world.getOrganimsCount(); i++) {
        Tile* target = world.getOrganism(i)->getTile();
        if (typeid(target) == typeid(SosnowskyHogweed)) {
            size_t distance = getDistanceTo(target);
            if (distance < min_distance) {
                min_distance = distance;
                index = i;
            }
        }
    }
    return index;
};

Tile* CyberSheep::nextTileToSosnowskyHogweed(size_t index) {
    Tile* target = world.getOrganism(index)->getTile();
    const size_t distance = getDistanceTo(target);
    std::vector<Tile*> possible_moves;
    std::vector<Tile*> neighbours = target->getNeighbours();
    for (auto neighbour : neighbours) {
        if (getDistanceTo(neighbour) < distance) {
            possible_moves.push_back(neighbour);
        }
    }
    if (possible_moves.empty()) return nullptr;
    return possible_moves[rng.roll(0, possible_moves.size() - 1)];
};