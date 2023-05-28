#include <iostream>
#include <fstream>
#include "View.h"
#include <sstream>
#include <termios.h>
#include <unistd.h>

 int View::getch(void) {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

int View::homeScreen() {
    std::cout << "\033[?25l";    //hide cursor

    std::ifstream h(PATH + "homescreen");
    std::stringstream buffer;
    buffer << h.rdbuf();
    h.close();
    std::string home;
    char c;
    std::cout << buffer.str() << std::endl;

    cursor = 1;
    do {
        home = buffer.str();
        for (int i = 0; i < 2; i++)
            if (i == cursor - 1)
                home.replace(home.find("%" + std::to_string(i)), std::string("%0").size(), "►");
            else
                home.replace(home.find("%" + std::to_string(i)), std::string("%0").size(), " ");
        std::cout << "\033[H\033[2J" << home;
        c = getch();
        if (c == 27) //intercepts the arrow keys and moves the cursor accordingly
        {
            getch();
            switch (getch()) {
                case 65:
                    if (cursor-- <= 1) cursor = 1;
                    break;
                case 66:
                    if (cursor++ >= 2) cursor = 2;
            }
        }
    } while (c != 10);  //once the user has selected the option

    return cursor;
}

void View::printOptions(std::vector<std::string> elements, int type) {
    size_t pos;
    std::string s;

    std::cout << "\033[H\033[2J" << std::endl << "   Select ";
    switch (type) {
        case 0:
            std::cout << "an enemy:";
            break;
        case 1:
            std::cout << "a hero:";
            break;
        case 2:
            std::cout << "an inventory:";
    }
    std::cout << std::endl << "  ╭────────────────────────────╮" << std::endl;
    for (int k = 0; k < elements.size(); k++) {
        s = elements[k];
        for (int i = 0; s.length() < 25; i++) s += " ";
        if (s != ".DS_Store") {
            s += "│";
            if (k + 1 == cursor)
                std::cout << "  │ ► " << s << std::endl;
            else
                std::cout << "  │   " << s << std::endl;
        }
    }
    std::cout << "  ╰────────────────────────────╯";
}

void View::printScreen(const Entity &enemy, const Entity &hero) {
    std::string _art = art;
    std::string _screen = screen;

    std::string dummy = "";
    //bar : 42 = hp : maxhp
    //bar = 42*hp / maxhp
    for (int i = 0; i < 47; i++)
        if (i < 47 * enemy.getHp() / enemy.getMaxHp())
            dummy += "▆";
        else
            dummy += " ";
    _screen.replace(_screen.find("%1"), std::string("%0").size(), dummy);

    _screen.replace(_screen.find("%2"), std::string("%0").size(), _art);

    dummy.clear();
    for (int i = 0; i < 18; i++)
        if (i < 18 * hero.getHp() / hero.getMaxHp())
            dummy += "▆";
        else
            dummy += " ";
    _screen.replace(_screen.find("%4"), std::string("%0").size(), dummy);

    dummy.clear();
    for (int i = 0; i < 18; i++)
        if (i < 18 * hero.getMp() / hero.getMaxMp())
            dummy += "▆";
        else
            dummy += " ";
    _screen.replace(_screen.find("%5"), std::string("%0").size(), dummy);

    for (int i = 0; i <
                    4; i++)  //the cursors has 4 possibile positions, 1 (top left) 2 (bottom left) 3 (top right) 4 (bottom right)
        if (cursor - 1 == i)
            _screen.replace(_screen.find("%" + std::to_string(i + 6)), std::string("%0").size(), "►");
        else
            _screen.replace(_screen.find("%" + std::to_string(i + 6)), std::string("%0").size(), " ");

    int diag1lim = (DIALOGS[1].find("▼") != std::string::npos) ? 53 : 51; //if dialog[1] contains '▼', its length is 53
    for (int i = 0; DIALOGS[0].length() < 51; i++) DIALOGS[0] += " ";
    for (int i = 0; DIALOGS[1].length() < diag1lim; i++) DIALOGS[1] += " ";
    _screen.replace(_screen.find("%10"), std::string("%10").size(), DIALOGS[0].substr(0, 51));
    _screen.replace(_screen.find("%11"), std::string("%10").size(), DIALOGS[1].substr(0, diag1lim));

    for (int i = 0; i < 4; i++) {
        for (int k = 0; OPTIONS[i].length() < 9; k++) OPTIONS[i] += " ";
        OPTIONS[i] = OPTIONS[i].substr(0, 9);
        if (OPTIONS[i][8] != ' ') OPTIONS[i][8] = '.';
        _screen.replace(_screen.find("%" + std::to_string(i + 12)), std::string("%10").size(), OPTIONS[i]);
    }

    //system("clear");
    std::cout << "\033[H\033[2J" << _screen;
}

int View::getCursor() const {
    return cursor;
}

void View::setCursor(int cursor) {
    View::cursor = cursor;
}

int View::incrementCursor() {
    return cursor++;
}

int View::decrementCursor() {
    return cursor--;
}

const std::string &View::getScreen() const {
    return screen;
}

void View::setScreen(const std::string &screen) {
    View::screen = screen;
}

const std::string &View::getArt() const {
    return art;
}

void View::setArt(const std::string &art) {
    View::art = art;
}

void View::notEnough(std::string type) {
    DIALOGS[0] = "Not enough " + type + "s!";
    DIALOGS[1] = "                                                  ▼";
}
