#pragma once

#include <iostream>

#include "../Simulator/Tile.hpp"
#include "../Simulator/World.hpp"  // Include the World class definition

class World;

class Display {
   private:
    World &world;

   public:
    Display(World &world);
    ~Display();

    void log(const std::string &message) const;
    void update() const;
};