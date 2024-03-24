#pragma once

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <vector>

#include "../Simulator/Organisms/@Organism.hpp"
#include "../Simulator/Organisms/OrganismFactoryJson.hpp"
#include "../Simulator/World.hpp"

enum class Mode : uint8_t { R, W, A, RW };
class FileHandler {
   private:
    const std::string filename;
    std::fstream file;

   public:
    void saveWorld(const World& world) {
        nlohmann::json json;
        nlohmann::json jsonOrganisms = nlohmann::json::array();
        const auto organisms = world.getOrganisms();
        if (organisms.empty()) return;
        for (auto organism : organisms) {
            jsonOrganisms.push_back(organism->toJson());
        }
        json["organisms"] = jsonOrganisms;
        json["time"] = world.checkTime();
        json["width"] = world.getWidth();
        json["height"] = world.getHeight();
        file << json.dump(2);
    };

    void loadWorld(World& world) {
        OrganismFactoryJson factory;
        nlohmann::json json;
        file >> json;
        size_t width = json["width"];
        size_t height = json["height"];
        size_t time = json["time"];
        world.setWorld(width, height, time);
        std::vector<Organism*> organisms;
        for (auto& organism : json["organisms"]) {
            organisms.push_back(factory.create(
                organism["type"].get<Organism::Type>(), organism, world));
        }
        world.setOrganisms(organisms);
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