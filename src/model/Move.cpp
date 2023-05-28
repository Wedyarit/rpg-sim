#include "Move.h"

const std::string &Move::getName() const {
    return name;
}

void Move::setName(const std::string &name) {
    Move::name = name;
}

int Move::getBasePower() const {
    return basePower;
}

void Move::setBasePower(int basePower) {
    Move::basePower = basePower;
}

int Move::getMpCost() const {
    return mpCost;
}

void Move::setMpCost(int mpCost) {
    Move::mpCost = mpCost;
}

int Move::getHpCost() const {
    return hpCost;
}

void Move::setHpCost(int hpCost) {
    Move::hpCost = hpCost;
}

int Move::getDefBuf() const {
    return defBuf;
}

void Move::setDefBuf(int defBuf) {
    Move::defBuf = defBuf;
}

int Move::getAtkBuf() const {
    return atkBuf;
}

void Move::setAtkBuf(int atkBuf) {
    Move::atkBuf = atkBuf;
}

int Move::getMagBuf() const {
    return magBuf;
}

void Move::setMagBuf(int magBuf) {
    Move::magBuf = magBuf;
}
