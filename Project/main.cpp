#include <iostream>

#include "FiguryPlaskie/Trapez.h"
using namespace std;
int main() {
    Trapez trapez(2, 4, 2, 2, 2);

    cout << trapez;
    cout << " ->Pole: " << trapez.Pole() << endl;
    cout << " ->Obwod: " << trapez.Obwod() << endl;

    return 0;
}