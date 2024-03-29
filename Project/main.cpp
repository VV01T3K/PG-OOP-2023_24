#include <array>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <string>

#include "Utils/FtxMyDisplay.hpp"

int main() {
    using namespace ftxui;
    using namespace std;
    FtxMyDisplay display;

    display.menu();

    return EXIT_SUCCESS;
}