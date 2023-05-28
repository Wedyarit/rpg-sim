#pragma once

#include "Move.h"
#include <string>
#include <sstream>
#include "../../include/json.hpp"

class Entity {
    static const int MOVES_NUMBER = 4;

    int mp, hp, atk, def, mag, maxHp, maxMp, atkBuf, defBuf, magBuf;
    Move moves[MOVES_NUMBER];
    std::string name;

public:
    Entity(std::istream &f);

    static bool critical();

    void getDamage(int damage);

    void updateStats(int _atk, int _def, int _mag);

    bool checkKO() const;

    void resetStats();

    void heal(int _hp, int _mp);

    static const int getMovesNumber();

    int getMp() const;

    void setMp(int mp);

    int getHp() const;

    void setHp(int hp);

    int getAtk() const;

    void setAtk(int atk);

    int getDef() const;

    void setDef(int def);

    int getMag() const;

    void setMag(int mag);

    int getMaxHp() const;

    void setMaxHp(int maxHp);

    int getMaxMp() const;

    void setMaxMp(int maxMp);

    int getAtkBuf() const;

    void setAtkBuf(int atkBuf);

    int getDefBuf() const;

    void setDefBuf(int defBuf);

    int getMagBuf() const;

    void setMagBuf(int magBuf);

    const Move *getMoves() const;

    const std::string &getName() const;

    void setName(const std::string &name);

    Entity();
};