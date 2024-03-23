#include "Tile.hpp"

Tile::Tile() {
    directions.fill(nullptr);
    organisms.reserve(1);
}
Tile::~Tile(){};

void Tile::clear() { organisms.clear(); }

void Tile::setLink(Direction direction, Tile *tile) {
    directions[static_cast<size_t>(direction)] = tile;
}

Organism *Tile::getOrganism() const { return organisms[0]; }
void Tile::placeOrganism(Organism *organism) { organisms.push_back(organism); }
void Tile::removeOrganism(Organism *organism) {
    organisms.erase(std::remove(organisms.begin(), organisms.end(), organism),
                    organisms.end());
}

Tile *Tile::getRandomFreeNeighbour() const {
    std::vector<Tile *> neighbours;
    for (auto &direction : directions) {
        if (direction != nullptr && direction->isFree()) {
            neighbours.push_back(direction);
        }
    }
    if (neighbours.empty()) return nullptr;
    return neighbours[RandGen::getInstance().roll(0, neighbours.size() - 1)];
}

Tile *Tile::getNeighbour(Direction direction) const {
    return directions[static_cast<size_t>(direction)];
}
Tile *Tile::getRandomNeighbour() const {
    std::vector<Tile *> neighbours;
    for (auto &direction : directions) {
        if (direction != nullptr) {
            neighbours.push_back(direction);
        }
    }
    if (neighbours.empty()) return nullptr;
    return neighbours[RandGen::getInstance().roll(0, neighbours.size() - 1)];
}
Direction Tile::getRandomDirection() const {
    std::vector<Direction> directions;
    for (auto &direction : this->directions) {
        if (direction != nullptr) {
            directions.push_back(
                static_cast<Direction>(&direction - &this->directions[0]));
        }
    }
    if (directions.empty()) return Direction::SELF;
    return directions[RandGen::getInstance().roll(0, directions.size() - 1)];
}

bool Tile::isFree() const { return organisms.empty(); }
