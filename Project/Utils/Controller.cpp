#include "Controller.hpp"
using namespace std;
Controller::Controller(){};
Controller::~Controller(){};
void Controller::PressToContinue() const {
    cout << "Press any key to continue...\n";
    cin.get();
    cout << "\033[2J\033[1;1H";
}