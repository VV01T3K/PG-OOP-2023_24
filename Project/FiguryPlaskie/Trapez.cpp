#include "Trapez.h"

#include <iostream>
using namespace std;
Trapez::Trapez(double podstawa1, double podstawa2, double bok1, double bok2,
               double wysokosc)
    : a(podstawa1), b(podstawa2), c(bok1), d(bok2), h(wysokosc) {
    cout << "Konstruktor Trapezu(" << a << "," << b << "," << c << "," << d
         << "," << h << ")" << endl;
}
double Trapez::GetA() const { return a; }
double Trapez::GetB() const { return b; }
double Trapez::GetC() const { return c; }
double Trapez::GetD() const { return d; }
double Trapez::GetH() const { return h; }
void Trapez::SetA(double a) { this->a = a; }
void Trapez::SetB(double b) { this->b = b; }
void Trapez::SetC(double c) { this->c = c; }
void Trapez::SetD(double d) { this->d = d; }
void Trapez::SetH(double h) { this->h = h; }
double Trapez::Obwod() { return a + b + c + d; }
double Trapez::Pole() { return (a + b) * h / 2; }
void Trapez::Wypisz(std::ostream& out) const {
    out << "Trapez(" << a << "," << b << "," << c << "," << d << "," << h
        << ")";
}
Trapez::~Trapez() {
    cout << "Destruktor Trapezu(" << a << "," << b << "," << c << "," << d
         << "," << h << ")" << endl;
}
