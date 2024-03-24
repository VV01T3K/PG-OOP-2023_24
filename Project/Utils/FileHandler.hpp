#pragma once

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <vector>

#include "../Simulator/Organisms/@Organism.hpp"
#include "../Simulator/Organisms/OrganismFactory.hpp"
#include "../Simulator/World.hpp"

enum class Mode : uint8_t { R, W, A, RW };
class FileHandler {
   private:
    const std::string filename;
    std::fstream file;

   public:
    void saveOrganisms(std::vector<Organism*> organisms) {
        if (organisms.empty()) return;
        nlohmann::json json;
        for (auto organism : organisms) {
            json.push_back(organism->toJson());
        }
        file << json.dump(4);
    };
    std::vector<Organism*> loadOrganisms(World& world) {
        nlohmann::json json;
        file >> json;
        OrganismFactoryJson factory;
        std::vector<Organism*> organisms;
        for (auto& organismJson : json) {
            Organism::Type type = Organism::Type(organismJson["type"]);
            Organism* organism = factory.create(type, organismJson, world);
            organisms.push_back(organism);
        }
        world.setOrganisms(organisms);
        return organisms;
    };
    FileHandler(std::string targetFilename, Mode mode = Mode::RW)
        : filename("../Project/" + targetFilename) {
        switch (mode) {
            case Mode::R:
                file.open(filename, std::ios::in);
                break;
            case Mode::W:
                file.open(filename, std::ios::out);
                break;
            case Mode::A:
                file.open(filename, std::ios::app);
                break;
            default:
                file.open(filename, std::ios::in | std::ios::out);
                break;
        }

        if (!file.is_open()) throw std::runtime_error("File not opened");
    };

    ~FileHandler() { file.close(); };
};