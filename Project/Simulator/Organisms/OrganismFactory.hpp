#pragma once
#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <vector>

#include "../World.hpp"
#include "@[OrganismPack].hpp"

class OrganismFactoryJson {
   public:
    Organism* createOrganism(Organism::Type type, const nlohmann::json& j,
                             World& world) {
        switch (type) {
            case Organism::Type::ANTELOPE:
                return new Antelope(j, world);
            case Organism::Type::CYBER_SHEEP:
                return new CyberSheep(j, world);
            case Organism::Type::FOX:
                return new Fox(j, world);
            case Organism::Type::HUMAN:
                return new Human(j, world);
            case Organism::Type::SHEEP:
                return new Sheep(j, world);
            case Organism::Type::TURTLE:
                return new Turtle(j, world);
            case Organism::Type::WOLF:
                return new Wolf(j, world);
            case Organism::Type::GRASS:
                return new Grass(j, world);
            case Organism::Type::GUARANA:
                return new Guarana(j, world);
            case Organism::Type::MILKWEED:
                return new Milkweed(j, world);
            case Organism::Type::SOSNOWSKY_HOGWEED:
                return new SosnowskyHogweed(j, world);
            case Organism::Type::WOLF_BERRIES:
                return new WolfBerries(j, world);
            default:
                throw std::invalid_argument("Invalid type");
        }
    }
};