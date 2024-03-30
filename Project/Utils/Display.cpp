#include "Display.hpp"

#include <iostream>

#include "../Simulator/Organisms/Animals/Human.hpp"
#include "FileHandler.hpp"

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
    topRight = newwin(LINES / 1.5 + .5, COLS / 2, 1, COLS / 2);
    bottomRight = newwin(LINES - (LINES / 1.5) - 1, COLS / 2,
                         (LINES + 1) / 1.5 + 1, COLS / 2);
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

void Display::eraseWindows() const {
    werase(left);         // Clear the left window
    werase(topRight);     // Clear the topRight window
    werase(bottomRight);  // Clear the bottomRight window
}

void Display::menu(bool &endFlag) const {
    eraseWindows();  // Clear the windows

    bool exitFlag = false;

    while (!exitFlag) {
        // Print the menu in the left window
        bool shift = false;
        if (world.checkTime() > 0) {
            mvwprintw(left, 1, 1, "%d. Continue the game", 1);
            shift = true;
        }
        mvwprintw(left, 1 + shift, 1, "%d. Start the game", 1 + shift);
        mvwprintw(left, 2 + shift, 1, "%d. Load the game", 2 + shift);
        mvwprintw(left, 3 + shift, 1, "%d. Save the game", 3 + shift);
        mvwprintw(left, 4 + shift, 1, "%d. Exit", 4 + shift);

        refreshWindows();  // Refresh the windows

        int ch = wgetch(left);
        if (ch == 'q' || ch == KEY_EXIT || ch == CTRL('c')) {
            endFlag = true;
            exitFlag = true;
            return;
        }

        switch (ch + !shift) {
            case '1':
                exitFlag = true;
                gameView();
                break;
            case '2':
                exitFlag = true;
                world.setWorld(world.getWidth(), world.getHeight(), 0);
                world.setOrganisms({});
                world.generateOrganisms();
                world.clearLogs();
                gameView();
                break;
            case '3': {
                FileHandler fileHandler("save.json");
                fileHandler.loadWorld(world);
            } break;
            case '4': {
                FileHandler fileHandler("save.json");
                fileHandler.saveWorld(world);
            } break;
            case '5':
                exitFlag = true;
                endFlag = true;
                break;
            default:
                break;
        }
    }
}
void Display::gameView() const {
    // bool exitFlag = false;
    // while (!exitFlag) {
    eraseWindows();  // Clear the windows

    // Get the maximum window size
    int max_y = 0, max_x = 0;
    getmaxyx(left, max_y, max_x);

    mvwprintw(bottomRight, 1, 1, "Time: %d", world.checkTime());
    mvwprintw(bottomRight, 2, 1, "Organisms: %d", world.getOrganisms().size());

    int shift_x = (max_x - world.getWidth() * 2) / 2;
    int shift_y = (max_y - world.getHeight()) / 2;
    // int shift_x = 1;
    // int shift_y = 1;

    // print error
    if (shift_x < 0 || shift_y < 0) {
        mvwprintw(left, 1, 1, "Window too small");
        refreshWindows();
        getch();
        return;
    }

    // Print the world in the left window
    for (size_t y = 0; y < (int)world.getHeight(); y++) {
        for (size_t x = 0; x < (int)world.getWidth(); x++) {
            Tile *tile = world.getTile(x, y);
            if (!tile->isFree()) {
                std::string str = tile->getOrganism()->getSymbol();
                std::wstring wstr(str.length(), L' ');  // Allocate enough space
                std::mbstowcs(&wstr[0], str.c_str(), str.length());  // Convert
                mvwaddwstr(left, y + shift_y, 2 * x + shift_x,
                           wstr.c_str());  // Draw the organism
            } else {
                mvwaddwstr(
                    left, y + shift_y, 2 * x + shift_x,
                    L"🔳");  // Shifted one to the right, Draw an empty tile
            }
        }
    }

    // Print the logs in the topRight window
    for (size_t i = 0; i < std::min(max_y, (int)world.getLogs().size()); i++) {
        mvwprintw(topRight, i + 1, 1, world.getLogs()[i].c_str());
    }

    refreshWindows();  // Refresh the windows

    //     exitFlag = true;
    // }
}