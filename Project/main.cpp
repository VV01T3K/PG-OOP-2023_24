#include <algorithm>  // Algorithms library, provides a collection of functions especially designed to be used on ranges of elements.
#include <cassert>  // Macro that can be used to verify assumptions made by the program and print a diagnostic message if this assumption is false.
#include <cctype>  // Functions to determine the type contained in character data.
#include <cmath>  // Declares a set of functions to compute common mathematical operations and transformations.
#include <fstream>  // Input/output stream class to operate on files.
#include <functional>  // Function objects, designed for use with the standard algorithms.
#include <iostream>  // Contains definitions of objects like cin, cout and cerr corresponding to the standard input, output and error streams.
#include <memory>    // General utilities to manage dynamic memory.
#include <random>    // Random number generators and distributions.
#include <stdexcept>  // Provides a set of standard exceptions that can be thrown from programs.
#include <string>  // Basic string library.
#include <utility>  // Includes utility functions and classes, like pair and swap.
#include <vector>  // STL dynamic array (vector) class template.
using namespace std;

#include <unistd.h>

#include "Simulator/Organisms/Animals/Dog.hpp"
#include "Simulator/Organisms/Animals/Sheep.hpp"
#include "Simulator/Tile.hpp"
#include "Simulator/World.hpp"

int main() {
    std::ios::sync_with_stdio(false);

    World world(4, 4);

    world.addOrganism(new Sheep(world), world.getTile(0));
    world.addOrganism(new Sheep(world), world.getTile(15));

    world.printOrganisms();
    while (true) {
        system("clear");

        world.simulate();

        world.printOrganisms();

        cout << world.getOrganimsCount() << endl;

        cin.get();
    }

    return 0;
}