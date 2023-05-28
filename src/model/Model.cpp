#include "Model.h"

Entity &Model::getEnemy() {
    return enemy;
}

void Model::setEnemy(const Entity &enemy) {
    Model::enemy = enemy;
}

Entity &Model::getHero() {
    return hero;
}

void Model::setHero(const Entity &hero) {
    Model::hero = hero;
}

Inventory &Model::getInventory() {
    return inventory;
}

void Model::setInventory(const Inventory &inventory) {
    Model::inventory = inventory;
}

Model::Model() {
    inventory = Inventory();
    hero = Entity();
    enemy = Entity();
}
