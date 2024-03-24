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
    Organism* createOrganism(Organism::Type type, const nlohmann::json& json,
                             World& world) {
        switch (type) {
            case Organism::Type::ANTELOPE:
                return new Antelope(json, world);
            case Organism::Type::CYBER_SHEEP:
                return new CyberSheep(json, world);
            case Organism::Type::FOX:
                return new Fox(json, world);
            case Organism::Type::HUMAN:
                return new Human(json, world);
            case Organism::Type::SHEEP:
                return new Sheep(json, world);
            case Organism::Type::TURTLE:
                return new Turtle(json, world);
            case Organism::Type::WOLF:
                return new Wolf(json, world);
            case Organism::Type::GRASS:
                return new Grass(json, world);
            case Organism::Type::GUARANA:
                return new Guarana(json, world);
            case Organism::Type::MILKWEED:
                return new Milkweed(json, world);
            case Organism::Type::SOSNOWSKY_HOGWEED:
                return new SosnowskyHogweed(json, world);
            case Organism::Type::WOLF_BERRIES:
                return new WolfBerries(json, world);
            default:
                throw std::invalid_argument("Invalid type");
        }
    }
};