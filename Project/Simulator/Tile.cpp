#include "Tile.hpp"

Tile::Tile(size_t index) : index(index) {
    directions.fill(nullptr);
    organisms.reserve(1);
}
Tile::~Tile(){};

void Tile::clear() { organisms.clear(); }

void Tile::setLink(Direction direction, Tile *tile) {
    directions[static_cast<u_int8_t>(direction)] = tile;
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
    return neighbours[RNG::roll(0, neighbours.size() - 1)];
}

Tile *Tile::getNeighbour(Direction direction) const {
    return directions[static_cast<u_int8_t>(direction)];
}
Tile *Tile::getRandomNeighbour() const {
    std::vector<Tile *> neighbours;
    for (auto &direction : directions) {
        if (direction != nullptr) {
            neighbours.push_back(direction);
        }
    }
    if (neighbours.empty()) return nullptr;
    return neighbours[RNG::roll(0, neighbours.size() - 1)];
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
    return directions[RNG::roll(0, directions.size() - 1)];
}

bool Tile::isFree() const { return organisms.empty(); }

std::vector<Tile *> Tile::getNeighbours() const {
    std::vector<Tile *> neighbours;
    for (auto &direction : directions) {
        if (direction != nullptr) {
            neighbours.push_back(direction);
        }
    }
    return neighbours;
}

std::vector<Tile *> Tile::getOccupiedNeighbours() const {
    std::vector<Tile *> neighbours;
    for (auto &direction : directions) {
        if (direction != nullptr && !direction->isFree()) {
            neighbours.push_back(direction);
        }
    }
    return neighbours;
}

size_t Tile::getOrganismCount() const { return organisms.size(); }

// TODO Refactor getDistanceTo
size_t Tile::getDistanceTo(const Tile *tile, size_t width) const {
    const long long x1 = index % width;
    const long long y1 = index / width;
    const long long x2 = tile->index % width;
    const long long y2 = tile->index / width;
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}