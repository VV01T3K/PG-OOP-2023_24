#pragma once
#include <vector>

#include "../Simulator/World.hpp"
class Display {
   private:
    /* data */
   public:
    void draw(World &world);
    Display(/* args */);
    ~Display();
};

Display::Display(/* args */) {}

Display::~Display() {}
