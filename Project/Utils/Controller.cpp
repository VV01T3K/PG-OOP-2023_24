#include "Controller.hpp"
using namespace std;
Controller::Controller(){};
Controller::~Controller(){};
void Controller::PressToContinue() const {
    cout << "Press any key to continue...\n";
    cin.get();
}