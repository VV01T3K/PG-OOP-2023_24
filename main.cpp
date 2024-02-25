#include "Prostokat.h"

int main() {
    Prostokat prostokat(5.0, 10.0);  // Create an instance of Prostokat with
                                     // width 5.0 and height 10.0

    std::cout << "Width: " << prostokat.GetA() << std::endl;
    std::cout << "Height: " << prostokat.GetB() << std::endl;
    std::cout << "Area: " << prostokat.Pole() << std::endl;

    return 0;
}