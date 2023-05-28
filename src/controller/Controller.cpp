#include <string>
#include "Controller.h"
#include <iostream>
#include <sstream>

Controller::Controller() {
    view = View();
    model = Model();

    if (view.homeScreen() == 1)
        mainMenu();
    else
        std::cout << "\033[H\033[2J\033[?25h";
}

void Controller::mainMenu() {
    char c;
    std::vector<std::string> elements;    //contains the availables enemies, heroes or items
    std::string types[3] = {"enemies", "heroes", "items"};

    for (int i = 0; i < 3; i++)    //for all the 3 categories, it makes the user select one
    {
        view.setCursor(1);
        elements = getJSON(types[i]); //gets the elements json files name
        do {
            view.printOptions(elements, i);
            c = View::getch();
            if (c == 27) //intercepts the arrow keys and moves the view.getCursor() accordingly
            {
                View::getch();
                switch (View::getch()) {
                    case 65:
                        if (view.decrementCursor() <= 1) view.setCursor(1);
                        break;
                    case 66:
                        if (view.incrementCursor() >= elements.size()) view.setCursor(elements.size());
                }
            }
        } while (c != 10);  //once the user has selected the option
        types[i] = elements[view.getCursor() - 1];  //it saves the name of the selected file
    }
    initEntities(types);
    mainLoop();
}

void Controller::initEntities(std::string *entities) {
    //initiates the entities and the needed files
    std::ifstream f;

    f.open(PATH + "enemies/" + entities[0] + ".json");
    model.setEnemy(Entity(f));
    f.close();

    f.open(PATH + "heroes/" + entities[1] + ".json");
    model.setHero(Entity(f));
    f.close();

    f.open(PATH + "items/" + entities[2] + ".json");
    model.setInventory(Inventory(f));
    f.close();

    std::ifstream t(PATH + "template");
    std::ifstream a;
    if (std::filesystem::exists(PATH + "arts/" + entities[0] + ".txt"))
        a.open(PATH + "arts/" + entities[0] + ".txt");
    else
        a.open(PATH + "arts/Slime.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();
    t.close();
    view.setScreen(buffer.str());
    buffer.str("");
    buffer << a.rdbuf();
    a.close();
    view.setArt(buffer.str());

    view.setCursor(1);
}

std::vector<std::string> Controller::getJSON(std::string type) {
    std::vector<std::string> elements;
    std::string s;
    for (const auto &entry: std::filesystem::directory_iterator(PATH + type + "/")) {
        s = entry.path().string().substr(entry.path().string().find(type + "/") + type.length() +
                                         1);
        s = s.substr(0, s.length() - 5);
        elements.push_back(s);
    }

    return elements;
}

void Controller::mainLoop() {
    int mode = 1; //1 main menu, 2 moves, 3 items, 4 run

    do {
        assignOptions(mode);
        mode = manageInput(mode);
    } while (mode != 4);
    View::DIALOGS[0] = model.getHero().getName() + " runs away!";
    View::DIALOGS[1] = "                                                  ▼";
    view.printScreen(model.getEnemy(), model.getHero());
    View::getch();
    view.homeScreen();
}

int Controller::manageInput(int mode) {
    char c;
    do {
        updateDialog(mode);

        view.printScreen(model.getEnemy(), model.getHero());
        c = View::getch();
        if (c == 27) {
            View::getch();
            switch (View::getch()) {   //1 (top left) 2 (bottom left) 3 (top right) 4 (bottom right)
                case 65:
                    if (view.getCursor() == 2) view.setCursor(1);
                    else if (view.getCursor() == 4) view.setCursor(3);
                    break;
                case 66:
                    if (view.getCursor() == 1) view.setCursor(2);
                    else if (view.getCursor() == 3) view.setCursor(4);
                    break;
                case 67:
                    if (view.getCursor() == 1) view.setCursor(3);
                    else if (view.getCursor() == 2) view.setCursor(4);
                    break;
                case 68:
                    if (view.getCursor() == 3) view.setCursor(1);
                    else if (view.getCursor() == 4) view.setCursor(2);
            }
        }
    } while (c != 10 && c != 'b');
    return nextMode(mode, c);
}

void Controller::updateDialog(int mode) {
    if (mode == 2) {
        if (model.getHero().getMoves()[view.getCursor() - 1].getName() != "") {
            View::DIALOGS[0] = model.getHero().getMoves()[view.getCursor() - 1].getName();
            View::DIALOGS[1] =
                    "MP Cost: " + std::to_string(model.getHero().getMoves()[view.getCursor() - 1].getMpCost()) +
                    "  HP Cost: " +
                    std::to_string(model.getHero().getMoves()[view.getCursor() - 1].getHpCost());
        } else {
            View::DIALOGS[0] = "Select a move.";
            View::DIALOGS[1] = "";
        }
    } else if (mode == 3) {
        if (model.getInventory().getItems()[view.getCursor() - 1].getName() != "") {
            View::DIALOGS[0] =
                    model.getInventory().getItems()[view.getCursor() - 1].getName() + " [" +
                    std::to_string(model.getInventory().getItems()[view.getCursor() - 1].getQuantity()) +
                    "] ";
            View::DIALOGS[1] = model.getInventory().getItems()[view.getCursor() - 1].getDescription();
        } else {
            View::DIALOGS[0] = "Select an item.";
            View::DIALOGS[1] = "";
        }
    } else {
        View::DIALOGS[0] = model.getHero().getName() + "'s turn!";
        View::DIALOGS[1] =
                "HP: " + std::to_string(model.getHero().getHp()) + "  MP: " + std::to_string(model.getHero().getMp());
    }
}

void Controller::assignOptions(int mode) {
    switch (mode) {
        case 1:
            View::OPTIONS[0] = "Fight";
            View::OPTIONS[1] = "Moves";
            View::OPTIONS[2] = "Items";
            View::OPTIONS[3] = "Run";
            View::DIALOGS[0] = model.getHero().getName() + "'s turn!";
            break;
        case 2:
            for (int i = 0; i < 4; i++)
                View::OPTIONS[i] = model.getHero().getMoves()[i].getName();
            View::DIALOGS[0] = "Select a move.";
            break;
        case 3:
            for (int i = 0; i < 4; i++)
                View::OPTIONS[i] = model.getInventory().getItems()[i].getName();
            View::DIALOGS[0] = "Select an item.";
            break;
    }
}

int Controller::nextMode(int mode, char c) {
    switch (mode) {
        case 1: //main menu
            if (c != 'b') {
                if (view.getCursor() == 1) //if user selected attack (mode 1 view.getCursor() 1)
                {
                    normalAttack(model.getHero(), model.getEnemy()); //base attack;
                    enemyTurn();
                }
                mode = view.getCursor();
                view.setCursor(1);
            }
            break;
        case 2: //moves
            if (c != 'b' && model.getHero().getMoves()[view.getCursor() - 1].getName() != "")  //if user choose a move
            {
                if (model.getHero().getMp() >=
                    model.getHero().getMoves()[view.getCursor() - 1].getMpCost())  //if enough mp
                {
                    if (model.getHero().getHp() >=
                        model.getHero().getMoves()[view.getCursor() - 1].getHpCost())  //if enough hp
                    {
                        useMove(view.getCursor() - 1, model.getHero(), model.getEnemy()); //performs the move
                        enemyTurn();    //gives the turn to the enemy
                        mode = 1;       //goes back to the main fight menu
                    } else {
                        view.notEnough("HP");
                        view.printScreen(model.getEnemy(), model.getHero());
                        View::getch();
                    }
                } else {
                    view.notEnough("MP");
                    view.printScreen(model.getEnemy(), model.getHero());
                    View::getch();
                }
            } else if (c == 'b') {   //if the users goes back to the previous menu
                mode = 1;   //goes back to the main fight menu
                view.setCursor(1);   //reset the cursor
            }
            break;
        case 3: //items
            if (c != 'b' &&
                model.getInventory().getItems()[view.getCursor() - 1].getName() != "")  //if user chosse an item
            {
                if (model.getInventory().getItems()[view.getCursor() - 1].getQuantity() > 0) {
                    useItem(view.getCursor() - 1);
                    enemyTurn();
                    mode = 1;
                } else {
                    view.notEnough("item");
                    view.printScreen(model.getEnemy(), model.getHero());
                    View::getch();
                }
            } else if (c == 'b') {
                mode = 1;
                view.setCursor(1);
            }
    }
    return mode;
}


void Controller::enemyTurn() {
    View::DIALOGS[0] = "Enemy's turn!";
    View::DIALOGS[1] = "                                                  ▼";
    view.printScreen(model.getEnemy(), model.getHero());
    View::getch();

    int prob = rand() % 100, k = 0;
    //lower the hp, lower the chance of using a normal attack
    //maxHp:30 = hp:chance
    if (prob < model.getEnemy().getHp() / 30 * model.getEnemy().getMaxHp())   //chanche of normal attack
        normalAttack(model.getEnemy(), model.getHero());
    else {
        prob = rand() % 4 - 1;
        do {
            k++;
            if (++prob > 3) prob = 0;
        } while (model.getEnemy().getMoves()[prob].getName() == "" && k <=
                                                                      4);   //tires different moves at most 4 times, then if all the moves are "" (the enemy has no moves) it performs basic attac
        if (k <= 4 && model.getEnemy().getMp() >= model.getEnemy().getMoves()[prob].getMpCost() &&
            model.getEnemy().getHp() >= model.getEnemy().getMoves()[prob].getHpCost())
            useMove(prob, model.getEnemy(), model.getHero()); //enemy performs the move only if it has enogh mps and hps
        else    //othervies it does a normal attack
            normalAttack(model.getEnemy(), model.getHero());
    }
    view.setCursor(1);
}

void Controller::winner(const std::string &name) {
    View::DIALOGS[0] = name + " wins!";
    View::DIALOGS[1] = "                                                  ▼";
    view.printScreen(model.getEnemy(), model.getHero());
    View::getch();
    view.homeScreen();
}


void Controller::normalAttack(Entity &entity, Entity &target) {
    int crit = (entity.critical()) ? 2 : 1;
    View::DIALOGS[0] = entity.getName() + " attacks!";
    View::DIALOGS[1] = (crit == 2) ? "A critical hit!                                   ▼"
                                   : "                                                  ▼";
    target.getDamage((entity.getAtk() / 3 + (entity.getAtk() * (entity.getAtk() - target.getDef()) / 200)) * crit);
    entity.resetStats();
    view.printScreen(model.getEnemy(), model.getHero());
    View::getch();
    if (target.checkKO())
        winner(entity.getName());
}

void Controller::useMove(int move, Entity &entity, Entity &target) {
    int crit = (entity.critical()) ? 2 : 1;
    View::DIALOGS[0] = entity.getName() + " uses " + entity.getMoves()[move].getName() + "!";
    View::DIALOGS[1] = (crit == 2) ? "A critical hit!                                   ▼"
                                   : "                                                  ▼";
    target.getDamage((entity.getMoves()[move].getBasePower() / 3 +
                      (entity.getMoves()[move].getBasePower() * (entity.getMag() - target.getDef()) / 200)) * crit);
    entity.heal(-entity.getMoves()[move].getHpCost(),
                -entity.getMoves()[move].getMpCost()); //this way, using the heal function to recalculate HPs and MPs, a move can also be curative
    entity.updateStats(entity.getMoves()[move].getAtkBuf(), entity.getMoves()[move].getDefBuf(),
                       entity.getMoves()[move].getMagBuf());


    entity.resetStats();
    view.printScreen(model.getEnemy(), model.getHero());
    View::getch();
    if (entity.checkKO())
        winner(target.getName());
    if (target.checkKO())
        winner(entity.getName());
}

void Controller::useItem(int item) {
    View::DIALOGS[0] = model.getInventory().getItems()[item].getName() + " used!";
    View::DIALOGS[1] = "                                                  ▼";
    model.getInventory().getItems()[item].setQuantity(model.getInventory().getItems()[item].getQuantity() - 1);
    model.getHero().heal(model.getInventory().getItems()[item].getHpHeal(),
                         model.getInventory().getItems()[item].getMpHeal());
    model.getHero().updateStats(model.getInventory().getItems()[item].getAtkBuf(),
                                model.getInventory().getItems()[item].getDefBuf(),
                                model.getInventory().getItems()[item].getMagBuf());
    view.printScreen(model.getEnemy(), model.getHero());
    View::getch();
}

