#pragma once

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <vector>

#include "../Simulator/Organisms/@Organism.hpp"

enum class Mode : uint8_t { R, W, A, RW, RA };
class FileHandler {
   private:
    std::string filename;
    std::fstream file;

   public:
    void saveOrganisms(std::vector<Organism*> organisms) {
        nlohmann::json json;
        for (auto organism : organisms) {
            json.push_back(organism->toJson());
        }
        file << json.dump(4);
    };
    // std::vector<Organism*> loadOrganisms();
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
            case Mode::RW:
                file.open(filename, std::ios::in | std::ios::out);
                break;
            case Mode::RA:
                file.open(filename, std::ios::in | std::ios::app);
                break;
            default:
                throw std::invalid_argument("Invalid mode");
        }
        if (!file.is_open()) throw std::runtime_error("File not opened");
    };

    ~FileHandler() { file.close(); };
};