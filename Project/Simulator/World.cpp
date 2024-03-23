#include "World.hpp"

World::World(size_t width, size_t height) : width(width), height(height) {
    tiles.reserve(width * height);
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            tiles.push_back(new Tile());
        }
    }
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            Tile *tile = tiles[y * width + x];
            if (y > 0) {
                tile->setLink(Direction::UP, tiles[(y - 1) * width + x]);
            }
            if (x < width - 1) {
                tile->setLink(Direction::RIGHT, tiles[y * width + x + 1]);
            }
            if (y < height - 1) {
                tile->setLink(Direction::DOWN, tiles[(y + 1) * width + x]);
            }
            if (x > 0) {
                tile->setLink(Direction::LEFT, tiles[y * width + x - 1]);
            }
        }
    }
};
World::~World() {
    for (auto organism : organisms) {
        delete organism;
    }
    for (auto tile : tiles) {
        delete tile;
    }
}

size_t World::getWidth() const { return width; }
size_t World::getHeight() const { return height; }

Tile *World::getTile(size_t index) const { return tiles[index]; }
Tile *World::getTile(size_t x, size_t y) const { return tiles[y * width + x]; }
void World::setTile(size_t x, size_t y, Tile *tile) {
    tiles[y * width + x] = tile;
}

Organism *World::getOrganism(size_t index) const { return organisms[index]; }

void World::addOrganism(Organism *organism, Tile *tile) {
    organisms.push_back(organism);
    organism->setTile(tile);
    tile->placeOrganism(organism);
}

void World::simulate() {
    const auto compare = [](const auto &a, const auto &b) {
        if (a->getInitiative() == b->getInitiative()) {
            return a->getAge() > b->getAge();
        }
        return a->getInitiative() > b->getInitiative();
    };
    std::sort(organisms.begin(), organisms.end(), compare);

    for (auto organism : organisms) {
        if (organism->isSkipped()) continue;
        if (organism->isDead()) continue;
        organism->action();
        for (auto other : organisms) {
            if (other->isDead()) continue;
            if (organism == other) continue;
            if (organism->getTile() == other->getTile())
                organism->collision(*other);
        }
    }

    const auto handlePostRound = [](auto &organism) {
        if (organism->isDead()) {
            organism->getTile()->removeOrganism(organism);
            return true;
        }
        organism->Age();
        organism->unskipTurn();
        return false;
    };

    organisms.erase(
        std::remove_if(organisms.begin(), organisms.end(), handlePostRound),
        organisms.end());
}

size_t World::getOrganimsCount() const { return organisms.size(); }
