#define _USE_MATH_DEFINES

#include "Kolo.h"

#include <cmath>
#include <iostream>
using namespace std;

#define π M_PI

Kolo::Kolo(double r) : r(r) { cout << "Konstruktor Koła(" << r << ")" << endl; }
double Kolo::GetR() const { return r; }
void Kolo::SetR(double r) { this->r = r; }
double Kolo::Obwod() { return 2 * π * r; }
double Kolo::Pole() { return π * r * r; }
void Kolo::Wypisz(std::ostream& out) const { out << "Koło o promieniu " << r; }
Kolo::~Kolo() { cout << "Destruktor Koła(" << r << ")" << endl; }
