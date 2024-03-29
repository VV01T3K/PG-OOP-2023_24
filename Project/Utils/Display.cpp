#include "Display.hpp"

#include <iostream>

#include "../Simulator/Organisms/Animals/Human.hpp"

using namespace std;

Display::Display(World &world) : world(world) {
    setlocale(LC_ALL, "");  // Set the locale to the default system locale
    initscr();              // Initialize the library
    start_color();          // Enable color
    use_default_colors();   // Use the terminal's default colors
    cbreak();               // Disable line buffering
    raw();                  // Disable line buffering
    keypad(stdscr, TRUE);   // Enable function and arrow keys
    noecho();               // Don't echo any keypresses
    curs_set(0);            // Hide the cursor
}

Display::~Display() {
    clear();                     // Clear the screen
    refresh();                   // Refresh the screen to show the new state
    mvprintw(0, 0, "Goodbye!");  // Print a goodbye message
    getch();                     // Wait for a key press
    endwin();
}

void Display::menu() const {
    // menu with ncurses

    int choice;
    bool exit = false;

    while (!exit) {
        clear();

        // Print the menu
        mvprintw(0, 0, "1. Start the game");
        mvprintw(1, 0, "2. Load the game");
        mvprintw(2, 0, "3. Save the game");
        mvprintw(3, 0, "4. Exit");

        choice = getch();  // Get the user's choice

        switch (choice) {
            case '1':
                exit = true;
                gameView();
                break;
            case '2':
                // loadGame();
                break;
            case '3':
                // saveGame();
                break;
            case '4':
                exit = true;
                break;
            default:
                break;
        }
    }
}
void Display::gameView() const {
    bool exit = false;
    // while (!exit) {
    clear();  // Clear the screen

    // Print time and world size
    mvprintw(0, 0, "Time: %d", world.checkTime());
    mvprintw(1, 0, "World size: %dx%d", world.getWidth(), world.getHeight());

    // Print the world
    for (size_t y = 0; y < world.getHeight(); y++) {
        for (size_t x = 0; x < world.getWidth(); x++) {
            Tile *tile = world.getTile(x, y);
            if (!tile->isFree()) {
                mvaddwstr(y + 3, x,
                          tile->getOrganism()
                              ->getSymbol()
                              .c_str());  // Draw the organism
            } else {
                mvaddwstr(y + 3, x, L"🔳");  // Draw an empty tile
            }
        }
    }

    // Print the number of entities
    mvprintw(world.getHeight() + 3, 0, "Entities: %d",
             world.getOrganimsCount());

    refresh();  // Refresh the screen to show the new state
    // }

    getch();  // Wait for a key press
}

// void Display::update() const {
//     cout << "Time: " << world.checkTime() << '\n';
//     cout << "World size: " << world.getWidth() << "x" << world.getHeight()
//          << '\n';
//     for (size_t y = 0; y < world.getHeight(); y++) {
//         for (size_t x = 0; x < world.getWidth(); x++) {
//             Tile *tile = world.getTile(x, y);
//             if (!tile->isFree()) {
//                 tile->getOrganism()->draw();
//             } else {
//                 cout << "🔳";
//             }
//         }
//         cout << '\n';
//     }
//     cout << "Entities: " << world.getOrganimsCount() << '\n';
// }