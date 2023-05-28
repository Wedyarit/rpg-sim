#pragma once

#include "Entity.h"
#include "Inventory.h"

class Model {
public:
    Model();

    Entity &getEnemy();

    void setEnemy(const Entity &enemy);

    Entity &getHero();

    void setHero(const Entity &hero);

    Inventory &getInventory();

    void setInventory(const Inventory &inventory);

private:
    Entity enemy, hero;
    Inventory inventory;
};
