#include <ncurses.h>
#define CTRL(c) ((c) & 037)

#include "Simulator/Organisms/[OrganismPack].hpp"
#include "Simulator/World.hpp"
#include "Utils/Controller.hpp"
#include "Utils/Display.hpp"
#include "Utils/FileHandler.hpp"

int main() {
    World world(10, 10);
    Display display(world);
    Controller controller(world, display);

    world.populateWorld();

    bool endFlag = false;
    display.menu(endFlag);
    while (true) {
        if (endFlag) break;
        if (controller.playerMove()) display.menu(endFlag);
        world.simulate();
        display.gameView();
    }

    return EXIT_SUCCESS;
}
