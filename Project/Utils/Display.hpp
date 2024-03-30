#pragma once
#define CTRL(c) ((c) & 037)
#include <locale.h>
#include <ncurses.h>

#include <iostream>
#include <string>
#include <vector>

#include "../Simulator/Tile.hpp"
#include "../Simulator/World.hpp"

class World;

class Display {
   private:
    World &world;
    WINDOW *left;
    WINDOW *topRight;
    WINDOW *bottomRight;

   public:
    Display(World &world);
    ~Display();
    void refreshWindows() const;
    void eraseWindows() const;
    void menu(bool &endFlag) const;
    void gameView() const;
    void worldPanel() const;
    std::string getSaveFileName() const;
    std::string chooseSave() const;
    std::pair<int, int> chooseWorldSize() const;
};