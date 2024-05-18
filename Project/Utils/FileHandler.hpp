#pragma once

#include <dirent.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <vector>

#include "../Simulator/Organisms/@Organism.hpp"
#include "../Simulator/World.hpp"
#include "OrganismFactory.hpp"

class FileHandler {
   private:
    enum class Mode : uint8_t { R, W, A, RW, RA };
    const std::string filename;
    std::fstream file;

    bool openFile(Mode mode) {
        if (file.is_open()) file.close();

        if (mode == Mode::R)
            file.open(filename, std::ios::in);
        else if (mode == Mode::W)
            file.open(filename, std::ios::out | std::ios::trunc);
        else if (mode == Mode::A)
            file.open(filename, std::ios::out | std::ios::app);
        else if (mode == Mode::RW)
            file.open(filename, std::ios::in | std::ios::out | std::ios::trunc);
        else if (mode == Mode::RA)
            file.open(filename, std::ios::in | std::ios::out | std::ios::app);
        else
            throw std::invalid_argument("Invalid mode");

        // if (!file.is_open()) throw std::runtime_error("Failed to open file");
        return file.is_open();
    }

    void closeFile() {
        if (file.is_open()) file.close();
    }

   public:
    void saveWorld(const World& world) {
        if (!openFile(Mode::W)) return;

        nlohmann::json json;
        nlohmann::json jsonOrganisms = nlohmann::json::array();

        const auto organisms = world.getOrganisms();
        if (organisms.empty()) return;
        for (auto organism : organisms) {
            jsonOrganisms.push_back(organism->toJson());
        }

        json["organisms"] = jsonOrganisms;
        json["world"] = {
            {"width", world.getWidth()},
            {"height", world.getHeight()},
            {"time", world.checkTime()},
        };
        file << json.dump(2);

        closeFile();
    };

    void loadWorld(World& world) {
        if (!openFile(Mode::R)) return;

        OrganismFactory factory;
        nlohmann::json json;
        file >> json;
        nlohmann::json world_json = json.at("world");
        size_t width = world_json.at("width").get<size_t>();
        size_t height = world_json.at("height").get<size_t>();
        size_t time = world_json.at("time").get<size_t>();
        world.setWorld(width, height, time);
        std::vector<Organism*> organisms;
        for (auto& organism : json["organisms"]) {
            organisms.push_back(factory.create(
                organism["type"].get<Organism::Type>(), organism, world));
        }
        world.setOrganisms(organisms);
        world.setHuman(world.findHuman());
        world.clearLogs();
        closeFile();
    };

    static std::vector<std::string> listSaves() {
        DIR* dir;
        struct dirent* ent;
        std::vector<std::string> files;

        if ((dir = opendir("../Project/Saves/")) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                std::string filename(ent->d_name);
                if (filename.size() >= 5 &&
                    filename.substr(filename.size() - 5) == ".json") {
                    filename = filename.substr(0, filename.size() - 5);
                    files.push_back(filename);
                }
            }
            closedir(dir);
        } else {
            throw std::runtime_error("Failed to open directory");
        }

        return files;
    }

    FileHandler(std::string targetFilename, Mode mode = Mode::RW)
        : filename("../Project/Saves/" + targetFilename){};

    ~FileHandler() { closeFile(); };
};