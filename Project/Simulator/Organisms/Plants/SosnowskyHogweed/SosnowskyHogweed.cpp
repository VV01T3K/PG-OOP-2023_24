#include "SosnowskyHogweed.hpp"

void SosnowskyHogweed::action() {
    Plant::action();
    for (auto& neighbour : tile->getOccupiedNeighbours()) {
        if (dynamic_cast<Plant*>(neighbour->getOrganism()) != nullptr) continue;
        if (typeid(*neighbour->getOrganism()) == typeid(CyberSheep)) continue;

        neighbour->getOrganism()->Die();
    }
}

bool SosnowskyHogweed::collisionReaction(Organism& other) {
    if (dynamic_cast<Plant*>(&other) != nullptr) return false;
    if (typeid(other) == typeid(CyberSheep)) return false;
    other.Die();
    Die();
    return true;
}