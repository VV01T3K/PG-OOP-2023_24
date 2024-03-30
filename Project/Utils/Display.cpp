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

    left = newwin(LINES - 1, COLS / 2, 1, 0);
    topRight = newwin(LINES / 1.5 + .5, COLS / 2, 1, COLS / 2);
    bottomRight = newwin(LINES - (LINES / 1.5) - 1, COLS / 2,
                         (LINES + 1) / 1.5 + 1, COLS / 2);
}

Display::~Display() {
    clear();              // Clear the screen
    refresh();            // Refresh the screen to show the new state
    delwin(left);         // Delete the left window
    delwin(topRight);     // Delete the topRight window
    delwin(bottomRight);  // Delete the bottomRight window
    endwin();             // End the library
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
    eraseWindows();

    bool exitFlag = false;

    while (!exitFlag) {
        bool shift = false;
        if (world.checkTime() > 0) {
            mvwprintw(left, 1, 1, "0. Continue the game");
            shift = true;
        }
        mvwprintw(left, 1 + shift, 1, "1. Start the game");
        mvwprintw(left, 2 + shift, 1, "2. Load the game");
        mvwprintw(left, 3 + shift, 1, "3. Save the game");
        mvwprintw(left, 4 + shift, 1, "4. Exit");

        refreshWindows();

        int width, height;

        int ch = wgetch(left);
        switch (ch) {
            // case Continue the game
            case '0':
                exitFlag = true;
                gameView();
                break;
            // case Start the game
            case '1':
                exitFlag = true;
                std::tie(width, height) = chooseWorldSize();
                world.resetWorld();
                world.setWorld(width, height, 0);
                world.populateWorld();
                gameView();
                break;
            // case Load the game
            case '2': {
                std::string saveName = chooseSave();
                if (saveName != "") {
                    FileHandler fileHandler(saveName);
                    fileHandler.loadWorld(world);
                    exitFlag = true;
                    gameView();
                }
            } break;
            // case Save the game
            case '3': {
                std::string fileName = getSaveFileName();
                if (fileName != "") {
                    FileHandler fileHandler(fileName);
                    fileHandler.saveWorld(world);
                }
            } break;
            // case Exit
            case '4':
            case KEY_EXIT:
            case CTRL('c'):
            case 'q':
                exitFlag = true;
                endFlag = true;
                break;
            default:
                break;
        }
    }
}
void Display::worldPanel() const {
    werase(bottomRight);
    std::string timeStr = "Time: " + to_string(world.checkTime());
    std::string organismsStr =
        "Organisms: " + to_string(world.getOrganimsCount());

    mvwprintw(bottomRight, 1, 1, "World:");
    mvwprintw(bottomRight, 2, 3, timeStr.c_str());
    mvwprintw(bottomRight, 3, 3, organismsStr.c_str());

    if (world.hasHuman()) {
        std::string nextMove =
            "Next move: " + world.getHuman()->getNextMoveSTR();
        std::string ability =
            "🔰 Immortality: " + world.getHuman()->getAbiliyInfo();

        mvwprintw(bottomRight, 4, 1, "Human:");
        mvwprintw(bottomRight, 5, 3, nextMove.c_str());
        mvwprintw(bottomRight, 6, 3, ability.c_str());
    } else
        mvwprintw(bottomRight, 4, 1, "No human in the world");

    mvwprintw(bottomRight, 8, 1,
              "Press 'enter' to confirm the move or 'q' to exit");

    refreshWindows();
}

void Display::gameView() const {
    eraseWindows();

    int max_y = 0, max_x = 0;
    getmaxyx(left, max_y, max_x);

    int shift_x = (max_x - world.getWidth() * 2) / 2;
    int shift_y = (max_y - world.getHeight()) / 2;
    if (shift_x < 0 || shift_y < 0) {
        mvwprintw(left, 1, 1, "Window too small");
        refreshWindows();
        getch();
        return;
    }

    worldPanel();

    for (size_t y = 0; y < (int)world.getHeight(); y++) {
        for (size_t x = 0; x < (int)world.getWidth(); x++) {
            Tile *tile = world.getTile(x, y);
            if (!tile->isFree()) {
                std::string str = tile->getOrganism()->getSymbol();
                std::wstring wstr(str.length(), L' ');
                std::mbstowcs(&wstr[0], str.c_str(), str.length());
                mvwaddwstr(left, y + shift_y, 2 * x + shift_x, wstr.c_str());
            } else {
                mvwaddwstr(left, y + shift_y, 2 * x + shift_x, L"🔳");
            }
        }
    }
    for (size_t i = 0; i < std::min(max_y, (int)world.getLogs().size()); i++) {
        mvwprintw(topRight, i + 1, 1, world.getLogs()[i].c_str());
    }
    refreshWindows();
}

std::string Display::getSaveFileName() const {
    eraseWindows();
    curs_set(1);

    int max_y = 0, max_x = 0;
    getmaxyx(left, max_y, max_x);

    mvwprintw(left, 1, 1, "Enter the name of the save file:");
    refreshWindows();

    char fileNameC[256];
    echo();
    mvwscanw(left, 2, 1, "%255s", fileNameC);
    noecho();
    if (fileNameC[0] == '\0') {
        curs_set(0);
        eraseWindows();
        return "";
    }
    string fileName = fileNameC + string(".json");

    curs_set(0);
    eraseWindows();
    return fileName;
}

std::string Display::chooseSave() const {
    eraseWindows();
    curs_set(1);

    std::vector<std::string> saves = FileHandler::listSaves();
    size_t i;
    for (i = 0; i < saves.size(); i++) {
        mvwprintw(left, i + 1, 1, saves[i].c_str());
    }

    int max_y = 0, max_x = 0;
    getmaxyx(left, max_y, max_x);

    mvwprintw(left, i + 2, 1, "Choose the save file:");
    refreshWindows();

    char fileNameC[256];
    echo();
    mvwscanw(left, i + 3, 1, "%255s", fileNameC);
    noecho();
    if (fileNameC[0] == '\0') {
        return "";
    }
    string fileName = fileNameC + string(".json");

    curs_set(0);
    eraseWindows();
    return fileName;
}

std::pair<int, int> Display::chooseWorldSize() const {
    eraseWindows();
    curs_set(1);

    int max_y = 0, max_x = 0;
    getmaxyx(left, max_y, max_x);

    mvwprintw(left, 1, 1, "Enter the width of the world:");
    refreshWindows();

    int width;
    echo();
    mvwscanw(left, 2, 1, "%d", &width);
    noecho();

    mvwprintw(left, 3, 1, "Enter the height of the world:");
    refreshWindows();

    int height;
    echo();
    mvwscanw(left, 4, 1, "%d", &height);
    noecho();

    curs_set(0);
    eraseWindows();
    return std::make_pair(width, height);
}