#include "Controller.hpp"

#include <ncurses.h>

#include "../Simulator/Organisms/Animals/Human.hpp"
#include "../Simulator/World.hpp"
#include "Display.hpp"

using namespace std;

#define KEY_SPACE 32

Controller::Controller(World &world, Display &display)
    : world(world), display(display) {}
Controller::~Controller(){};

bool Controller::input() {
    int key = 0;
    if (GlobalSettings::HUMAN_AI || !world.hasHuman()) {
        key = getch();
        if (key == KEY_EXIT || key == CTRL('c') || key == 'q') return true;
        return false;
    }
    do {
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
            case KEY_SPACE:
                world.getHuman()->toggleImortality();
                break;
            case 'q':
            case KEY_EXIT:
            case CTRL('c'):
                return true;
        }
        display.worldPanel();
    } while (key != '\n' || world.getHuman()->getNextMove() == Direction::SELF);
    // } while (key != '\n');
    return false;
}