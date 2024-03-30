#include "Controller.hpp"

#include "../Simulator/World.hpp"

using namespace std;

Controller::Controller(World &world) : world(world) {}
Controller::~Controller(){};

void Controller::playerMove() {
    int key = 0;
    while (key != 'q') {
        key = getch();
        switch (key) {
            case KEY_UP:
                // world.getHuman()->setNextMove(Direction::UP);
                break;
            case KEY_DOWN:
                break;
            case KEY_LEFT:
                break;
            case KEY_RIGHT:
                break;
            case 'q':
                break;
            default:
                break;
        }
    }
}