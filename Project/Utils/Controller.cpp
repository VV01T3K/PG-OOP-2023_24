#include "Controller.hpp"

#include <ncurses.h>

#include "../Simulator/Organisms/Animals/Human.hpp"
#include "../Simulator/World.hpp"
#include "Display.hpp"

using namespace std;

Controller::Controller(World &world, Display &display)
    : world(world), display(display) {}
Controller::~Controller(){};

bool Controller::playerMove() {
    int key = 0;
    while (key != '\n') {
        key = getch();
        switch (key) {
            case KEY_UP:
            case 'w':
                world.getHuman()->setNextMove(Direction::UP);
                break;
            case KEY_DOWN:
            case 's':
                world.getHuman()->setNextMove(Direction::DOWN);
                break;
            case KEY_LEFT:
            case 'a':
                world.getHuman()->setNextMove(Direction::LEFT);
                break;
            case KEY_RIGHT:
            case 'd':
                world.getHuman()->setNextMove(Direction::RIGHT);
                break;
            // space
            case 32:
                world.getHuman()->useAbility();
                break;
            case '\n':
                return false;
            default:
                if (key == 'q' || key == KEY_EXIT || key == CTRL('c'))
                    return true;
        }
        display.worldPanel();
    }
    return false;
}