#pragma once
#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <vector>

#include "../World.hpp"
#include "@[OrganismPack].hpp"

class OrganismFactory {
   public:
    Organism* createOrganism(Organism::Type type, const nlohmann::json& j,
                             World& world) {
        switch (type) {
            case Organism::Type::GRASS:
                return new Grass(j, world);

            default:
                throw std::invalid_argument("Invalid type");
        }
    }
};