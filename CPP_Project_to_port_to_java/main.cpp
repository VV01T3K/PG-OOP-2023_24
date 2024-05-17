#include "Simulator/World.hpp"
#include "Utils/Controller.hpp"
#include "Utils/Display.hpp"

int main() {
    World world;
    Display display(world);
    Controller controller(world, display);

    bool endFlag = false;
    display.menu(endFlag);
    while (true) {
        if (endFlag) break;
        if (controller.input()) display.menu(endFlag);
        world.simulate();
        display.gameView();
    }

    return EXIT_SUCCESS;
}
