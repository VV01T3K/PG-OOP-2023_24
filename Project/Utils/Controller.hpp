#pragma once

#include <iostream>

#include "../Simulator/World.hpp"

class Controller {
   private:
    World &world;

   public:
    Controller(World &world);
    ~Controller();
    void playerMove();
};