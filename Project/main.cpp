#include <iostream>

#include "FiguryPlaskie/Prostokat.h"
#include "FiguryPlaskie/Trapez.h"
#include "FiguryPlaskie/Trojkat.h"

using namespace std;
int main() {
    Trapez trapez(2, 4, 2, 2, 2);

    cout << trapez;
    cout << " ->Pole: " << trapez.Pole() << endl;
    cout << " ->Obwod: " << trapez.Obwod() << endl;

    cout << endl;

    Prostokat prostokat(4, 6);
    Trojkat trojkat(3, 4, 5);

    cout << endl;

    cout << prostokat << ", Pole: " << prostokat.Pole()
         << ", Obwod: " << prostokat.Obwod() << endl;
    cout << trojkat << ", Pole: " << trojkat.Pole()
         << ", Obwod: " << trojkat.Obwod() << endl;

    FiguraPlaska* figury[2];

    cout << endl;

    figury[0] = new Prostokat(8, 9);
    figury[1] = new Trojkat(6, 8, 10);

    cout << endl;

    for (int i = 0; i < 2; i++) {
        cout << *figury[i] << endl;
    }

    cout << endl;

    for (int i = 0; i < 2; i++) {
        delete figury[i];
    }

    return 0;
}