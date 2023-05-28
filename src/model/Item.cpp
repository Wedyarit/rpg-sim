#include "Item.h"

const std::string &Item::getName() const {
    return name;
}

void Item::setName(const std::string &name) {
    this->name = name;
}

const std::string &Item::getDescription() const {
    return description;
}

void Item::setDescription(const std::string &description) {
    this->description = description;
}

int Item::getHpHeal() const {
    return hpHeal;
}

void Item::setHpHeal(int hpHeal) {
    this->hpHeal = hpHeal;
}

int Item::getMpHeal() const {
    return mpHeal;
}

void Item::setMpHeal(int mpHeal) {
    this->mpHeal = mpHeal;
}

int Item::getDefBuf() const {
    return defBuf;
}

void Item::setDefBuf(int defBuf) {
    this->defBuf = defBuf;
}

int Item::getAtkBuf() const {
    return atkBuf;
}

void Item::setAtkBuf(int atkBuf) {
    this->atkBuf = atkBuf;
}

int Item::getMagBuf() const {
    return magBuf;
}

void Item::setMagBuf(int magBuf) {
    this->magBuf = magBuf;
}

int Item::getQuantity() const {
    return quantity;
}

void Item::setQuantity(int quantity) {
    this->quantity = quantity;
}
