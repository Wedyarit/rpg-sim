

#include "../view/View.h"
#include "../model/Model.h"

class Controller {
    inline static const std::string PATH = "/Users/wedyarit/Developer/rpg-simulator/res/";

public:
    Controller();
    View view;
    Model model;

    void mainMenu();

    void initEntities(std::string *entities);

    std::vector<std::string> getJSON(std::string type);

    void mainLoop();

    int manageInput(int mode);

    void updateDialog(int mode);
    void assignOptions(int mode);
    int nextMode(int mode, char c);
    void enemyTurn();
    void winner(const std::string& name);
    void useItem(int item);
    void useMove(int move, Entity &entity, Entity &target);
    void normalAttack(Entity &entity, Entity &target);
};