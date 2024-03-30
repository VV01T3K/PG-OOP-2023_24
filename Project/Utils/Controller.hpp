#pragma once

#include <iostream>

#include "../Simulator/World.hpp"
#include "Display.hpp"

class Controller {
   private:
    World &world;
    Display &display;

   public:
    Controller(World &world, Display &display);
    ~Controller();
    bool input();
};