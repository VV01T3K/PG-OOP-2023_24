#include "Immortality.hpp"

#include "../Organisms/@Organism.hpp"
#include "../Organisms/Animals/@Animal.hpp"
#include "../Organisms/Animals/Human.hpp"

void Immortality::effect(Organism& user, Organism& other) {
    Tile* newtile = user.getTile()->getRandomFreeNeighbour();
    if (newtile == nullptr) user.getTile()->getRandomNeighbour();
    if (newtile == nullptr) {
        dynamic_cast<Animal*>(&other)->undoMove();
        return;
    }
    dynamic_cast<Human*>(&user)->move(newtile);
    if (user.getTile()->getOrganismCount() > 1)
        user.collision(*user.getTile()->getOrganism());
}

void Immortality::effect(Organism& user) {
    Tile* newtile = user.getTile()->getRandomFreeNeighbour();
    dynamic_cast<Human*>(&user)->move(newtile);
    if (user.getTile()->getOrganismCount() > 1)
        user.collision(*user.getTile()->getOrganism());
}
