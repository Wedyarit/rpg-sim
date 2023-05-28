#include "Inventory.h"
#include "../../include/json.hpp"

Inventory::Inventory(std::istream &f) {
    nlohmann::json _inventory;
    f >> _inventory;

    for (int i = 0; i < 4; i++) {
        items[i].setName(_inventory[std::to_string(i)]["name"]);
        items[i].setMpHeal(_inventory[std::to_string(i)]["MP Heal"]);
        items[i].setHpHeal(_inventory[std::to_string(i)]["HP Heal"]);
        items[i].setDefBuf(_inventory[std::to_string(i)]["DEF Buf"]);
        items[i].setAtkBuf(_inventory[std::to_string(i)]["ATK Buf"]);
        items[i].setMagBuf(_inventory[std::to_string(i)]["MAG Buf"]);
        items[i].setDescription(_inventory[std::to_string(i)]["description"]);
        items[i].setQuantity(_inventory[std::to_string(i)]["quantity"]);
    }
}

Item *Inventory::getItems() {
    return items;
}

Inventory::Inventory() {

}
