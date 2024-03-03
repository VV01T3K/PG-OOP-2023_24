#include "Prostokat.h"

int main() {
    Prostokat prostokat(5.0, 10.0);

    std::cout << "Szerokość: " << prostokat.GetA() << std::endl;
    std::cout << "Wysokość: " << prostokat.GetB() << std::endl;
    std::cout << "Pole: " << prostokat.Pole() << std::endl;
    std::cout << "Obwód: " << prostokat.Obwod() << std::endl;

    return 0;
}