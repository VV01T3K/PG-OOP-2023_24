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

    const char *title = "Wojciech Siwiec s197815";
    mvwprintw(stdscr, 0, 0, title);
    refresh();

    // Create three windows
    left = newwin(LINES - 1, COLS / 2, 1, 0);
    topRight = newwin(LINES / 2 - 1, COLS / 2, 1, COLS / 2);
    bottomRight =
        newwin(LINES - (LINES / 2 + 1) + 1, COLS / 2, LINES / 2, COLS / 2);
}

Display::~Display() {
    clear();                     // Clear the screen
    refresh();                   // Refresh the screen to show the new state
    mvprintw(0, 0, "Goodbye!");  // Print a goodbye message
    getch();                     // Wait for a key press
    delwin(left);                // Delete the left window
    delwin(topRight);            // Delete the topRight window
    delwin(bottomRight);         // Delete the bottomRight window
    endwin();                    // End the library
}

void Display::refreshWindows() const {
    box(left, 0, 0);
    box(topRight, 0, 0);
    box(bottomRight, 0, 0);

    wrefresh(left);
    wrefresh(topRight);
    wrefresh(bottomRight);
}

void Display::clearWindows() const {
    werase(left);         // Clear the left window
    werase(topRight);     // Clear the topRight window
    werase(bottomRight);  // Clear the bottomRight window
}

void Display::menu() const {
    // menu with ncurses

    clearWindows();  // Clear the windows

    int choice;
    bool exit = false;

    while (!exit) {
        // Print the menu in the left window
        mvwprintw(left, 1, 1, "1. Start the game");
        mvwprintw(left, 2, 1, "2. Load the game");
        mvwprintw(left, 3, 1, "3. Save the game");
        mvwprintw(left, 4, 1, "4. Exit");

        refreshWindows();  // Refresh the windows

        choice = wgetch(left);  // Get the user's choice from the left window

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

    clearWindows();  // Clear the windows

    // Get the maximum window size
    int max_y = 0, max_x = 0;
    getmaxyx(left, max_y, max_x);

    // Print time and world size in the top right window
    mvwprintw(topRight, 1, 1, "Time: %d", world.checkTime());
    mvwprintw(topRight, 2, 1, "World size: %dx%d", world.getWidth(),
              world.getHeight());

    int shift_x = (max_x - world.getWidth() * 2) / 2;
    int shift_y = (max_y - world.getHeight()) / 2;

    // print error
    if (shift_x < 0 || shift_y < 0) {
        mvwprintw(left, 1, 1, "Window too small");
        refreshWindows();
        getch();
        return;
    }

    // Print the world in the left window
    for (size_t y = 0; y < std::min(max_y, (int)world.getHeight()); y++) {
        for (size_t x = 0; x < std::min(max_x, (int)world.getWidth()); x++) {
            Tile *tile = world.getTile(x, y);
            if (!tile->isFree()) {
                mvwaddwstr(left, y + shift_y,
                           x + shift_x,  // Shifted one to the right
                           tile->getOrganism()
                               ->getSymbol()
                               .c_str());  // Draw the organism
            } else {
                mvwaddwstr(
                    left, y + shift_y, x + shift_x,
                    L"🔳");  // Shifted one to the right, Draw an empty tile
            }
        }
    }

    // Print the number of entities in the bottom right window
    mvwprintw(bottomRight, world.getHeight() + 3, 1, "Entities: %d",
              world.getOrganimsCount());

    refreshWindows();  // Refresh the windows

    getch();  // Wait for a key press

    // Delete the windows when you're done with them
}