#include <iostream>

#include "FiguryPlaske/Kolo.h"
#include "FiguryPlaske/Prostokat.h"
#include "FiguryPlaske/Trojkat.h"

using namespace std;

int main() {
    // Tworzenie obiektów za pomocą zmiennych lokalnych
    Kolo kolo(5.0);
    Prostokat prostokat(4.0, 6.0);
    Trojkat trojkat(3.0, 4.0, 5.0);

    // Wyświetlanie właściwości obiektów
    cout << "Kolo: " << kolo << ", Pole: " << kolo.Pole()
         << ", Obwod: " << kolo.Obwod() << endl;
    cout << "Prostokat: " << prostokat << ", Pole: " << prostokat.Pole()
         << ", Obwod: " << prostokat.Obwod() << endl;
    cout << "Trojkat: " << trojkat << ", Pole: " << trojkat.Pole()
         << ", Obwod: " << trojkat.Obwod() << endl;

    // Tworzenie obiektów za pomocą wskaźników
    Kolo* pKolo = new Kolo(7.0);
    Prostokat* pProstokat = new Prostokat(8.0, 9.0);
    Trojkat* pTrojkat = new Trojkat(6.0, 8.0, 10.0);

    // Wyświetlanie właściwości obiektów
    cout << "Kolo: " << *pKolo << ", Pole: " << pKolo->Pole()
         << ", Obwod: " << pKolo->Obwod() << endl;
    cout << "Prostokat: " << *pProstokat << ", Pole: " << pProstokat->Pole()
         << ", Obwod: " << pProstokat->Obwod() << endl;
    cout << "Trojkat: " << *pTrojkat << ", Pole: " << pTrojkat->Pole()
         << ", Obwod: " << pTrojkat->Obwod() << endl;

    delete pKolo;
    delete pProstokat;
    delete pTrojkat;

    return 0;
}