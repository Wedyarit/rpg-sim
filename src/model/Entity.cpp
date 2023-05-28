#include "Entity.h"
#include <random>

Entity::Entity(std::istream &f) {
    nlohmann::json _ent;
    f >> _ent;

    name = _ent["name"];
    mp = _ent["mp"];
    hp = _ent["hp"];
    maxMp = _ent["mp"];
    maxHp = _ent["hp"];
    atk = _ent["atk"];
    def = _ent["def"];
    mag = _ent["mag"];
    atkBuf = 0;
    defBuf = 0;
    magBuf = 0;

    for (int i = 0; i < MOVES_NUMBER; i++) {
        moves[i].setName(_ent["moves"][std::to_string(i)]["name"]);
        moves[i].setBasePower(_ent["moves"][std::to_string(i)]["Base Power"]);
        moves[i].setMpCost(_ent["moves"][std::to_string(i)]["MP Cost"]);
        moves[i].setHpCost(_ent["moves"][std::to_string(i)]["HP Cost"]);
        moves[i].setDefBuf(_ent["moves"][std::to_string(i)]["DEF Buf"]);
        moves[i].setAtkBuf(_ent["moves"][std::to_string(i)]["ATK Buf"]);
        moves[i].setMagBuf(_ent["moves"][std::to_string(i)]["MAG Buf"]);
    }
}

bool Entity::critical() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 99);
    return (dist(gen) < 10);
}


void Entity::getDamage(int damage) {
    hp -= damage;
}

void Entity::updateStats(int atk, int def, int mag) {
    this->atk -= atkBuf;
    this->def -= defBuf;
    this->mag -= magBuf;
    this->atkBuf += atk;
    this->defBuf += def;
    this->magBuf += mag;
    this->atk += atkBuf;
    this->def += defBuf;
    this->mag += magBuf;
}

bool Entity::checkKO() const {
    return (hp <= 0);
}

void Entity::resetStats() {
    atk -= atkBuf;
    def -= defBuf;
    mag -= magBuf;
    atkBuf = 0;
    defBuf = 0;
    magBuf = 0;
}

void Entity::heal(int hp, int mp) {
    this->hp += hp;
    if (hp > maxHp) this->hp = maxHp;
    this->mp += mp;
    if (mp > maxMp) this->mp = maxMp;
}


const int Entity::getMovesNumber() {
    return MOVES_NUMBER;
}

int Entity::getMp() const {
    return mp;
}

void Entity::setMp(int mp) {
    Entity::mp = mp;
}

int Entity::getHp() const {
    return hp;
}

void Entity::setHp(int hp) {
    Entity::hp = hp;
}

int Entity::getAtk() const {
    return atk;
}

void Entity::setAtk(int atk) {
    Entity::atk = atk;
}

int Entity::getDef() const {
    return def;
}

void Entity::setDef(int def) {
    Entity::def = def;
}

int Entity::getMag() const {
    return mag;
}

void Entity::setMag(int mag) {
    Entity::mag = mag;
}

int Entity::getMaxHp() const {
    return maxHp;
}

void Entity::setMaxHp(int maxHp) {
    Entity::maxHp = maxHp;
}

int Entity::getMaxMp() const {
    return maxMp;
}

void Entity::setMaxMp(int maxMp) {
    Entity::maxMp = maxMp;
}

int Entity::getAtkBuf() const {
    return atkBuf;
}

void Entity::setAtkBuf(int atkBuf) {
    Entity::atkBuf = atkBuf;
}

int Entity::getDefBuf() const {
    return defBuf;
}

void Entity::setDefBuf(int defBuf) {
    Entity::defBuf = defBuf;
}

int Entity::getMagBuf() const {
    return magBuf;
}

void Entity::setMagBuf(int magBuf) {
    Entity::magBuf = magBuf;
}

const Move *Entity::getMoves() const {
    return moves;
}

const std::string &Entity::getName() const {
    return name;
}

void Entity::setName(const std::string &name) {
    Entity::name = name;
}

Entity::Entity() {

}
