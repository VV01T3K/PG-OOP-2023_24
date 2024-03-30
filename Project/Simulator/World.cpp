#include "World.hpp"

#include "Organisms/Animals/Human.hpp"
#include "Organisms/[OrganismPack].hpp"

void World::createBoard(size_t width, size_t height) {
    tiles.reserve(width * height);
    for (size_t i = 0; i < width * height; i++) {
        tiles.push_back(new Tile(i));
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
}

World::World(size_t width, size_t height) : width(width), height(height) {
    createBoard(width, height);
};

void World::setWorld(size_t width, size_t height, size_t time) {
    this->clearTiles();
    this->width = width;
    this->height = height;
    this->time = time;
    createBoard(width, height);
}

World::~World() {
    for (auto organism : organisms) {
        delete organism;
    }
    for (auto tile : tiles) {
        delete tile;
    }
    delete logs;
}
size_t World::checkTime() const { return time; }

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
    time++;
    clearLogs();
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
        if (!GlobalSettings::AI_ACTION && typeid(*organism) != typeid(Human))
            continue;
        organism->action();

        for (auto other : organisms) {
            if (other->isDead()) continue;
            if (organism == other) continue;
            if (organism->getTile() == other->getTile())
                organism->collision(*other);
        }
    }

    const auto handlePostRound = [&](auto &organism) {
        if (organism->isDead()) {
            organism->getTile()->removeOrganism(organism);
            if (typeid(*organism) == typeid(Human)) human = nullptr;
            delete organism;
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

void World::spreadOrganisms(Organism *organism, size_t count) {
    if (count > 0) {
        const size_t max = width * height;
        while (true) {
            if (getOrganimsCount() == max) break;
            Tile *tile = tiles[RNG::roll(0, tiles.size() - 1)];
            if (tile->isFree()) {
                addOrganism(organism->construct(), tile);
                if (!--count) break;
            }
        }
    }
    delete organism;
}

void World::linkOrganismsWithTiles() {
    for (auto organism : organisms) {
        getTile(organism->getTile()->index)->placeOrganism(organism);
    }
}

std::vector<Organism *> World::getOrganisms() const { return organisms; }

void World::setOrganisms(std::vector<Organism *> organisms) {
    this->clearOrganisms();
    this->organisms = organisms;
    linkOrganismsWithTiles();
}

void World::clearOrganisms() {
    for (auto organism : organisms) {
        delete organism;
    }
    organisms.clear();
    human = nullptr;
}
void World::clearTiles() {
    for (auto tile : tiles) {
        delete tile;
    }
    tiles.clear();
}
void World::cleanTiles() {
    for (auto tile : tiles) {
        tile->clear();
    }
}

void World::resetWorld() {
    clearOrganisms();
    cleanTiles();
    clearLogs();
    time = 0;
}

void World::populateWorld() {
    resetWorld();

    spreadOrganisms(new Human(*this), 1);
    setHuman(organisms.back());

    // spreadOrganisms(new SosnowskyHogweed(*this), 3);
    // spreadOrganisms(new Grass(*this), 2);
    // spreadOrganisms(new Guarana(*this), 2);
    // spreadOrganisms(new Milkweed(*this), 1);
    spreadOrganisms(new WolfBerries(*this), 10);

    // spreadOrganisms(new Wolf(*this), 4);
    // spreadOrganisms(new Sheep(*this), 4);
    // spreadOrganisms(new CyberSheep(*this), 10);
    // spreadOrganisms(new Fox(*this), 2);
    // spreadOrganisms(new Turtle(*this), 2);
    // spreadOrganisms(new Antelope(*this), 1);
}

void World::addLog(std::string log) { logs->push_back(log); }
const std::vector<std::string> &World::getLogs() const { return *logs; }
void World::clearLogs() { logs->clear(); }

void World::setHuman(Human *human) { this->human = human; }
void World::setHuman(Organism *organism) {
    human = dynamic_cast<Human *>(organism);
}
Human *World::getHuman() const { return human; }
bool World::hasHuman() const { return human != nullptr; }
Human *World::findHuman() const {
    for (auto organism : organisms) {
        if (typeid(*organism) == typeid(Human)) {
            return dynamic_cast<Human *>(organism);
        }
    }
    return nullptr;
}