
#include "../model/Entity.h"

class View {
    inline static const std::string PATH = "/Users/wedyarit/Developer/rpg-simulator/res/";
    std::string screen, art;
public:
    int cursor = 1;
    inline static std::string DIALOGS[2] = {"line1", "line2"};
    inline static std::string OPTIONS[4] = {"Fight", "Moves", "Items", "Run"};

    static int getch();
    int getCursor() const;
    int incrementCursor();
    int decrementCursor();

    void printOptions(std::vector<std::string> elements, int type);

    void setCursor(int cursor);

    int homeScreen();

    void mainMenu();

    void printScreen(const Entity &enemy, const Entity &hero);

    const std::string &getScreen() const;

    void setScreen(const std::string &screen);

    const std::string &getArt() const;

    void setArt(const std::string &art);

    void notEnough(std::string type);
};