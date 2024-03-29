#pragma once

#include <locale.h>
#include <ncurses.h>

#include <iostream>
#include <string>
#include <vector>

#include "../Simulator/Tile.hpp"
#include "../Simulator/World.hpp"  // Include the World class definition

class World;

class Display {
   private:
    World &world;

   public:
    Display(World &world);
    ~Display();

    void menu() const;
    void gameView() const;
    // void saveGame() const;
    // void loadGame() const;
};