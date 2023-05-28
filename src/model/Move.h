#pragma once

#include <string>

class Move {
    std::string name;
    int basePower, mpCost, hpCost, defBuf, atkBuf, magBuf;

public:
    const std::string &getName() const;
    void setName(const std::string &name);

    int getBasePower() const;
    void setBasePower(int basePower);

    int getMpCost() const;
    void setMpCost(int mpCost);

    int getHpCost() const;
    void setHpCost(int hpCost);

    int getDefBuf() const;
    void setDefBuf(int defBuf);

    int getAtkBuf() const;
    void setAtkBuf(int atkBuf);

    int getMagBuf() const;
    void setMagBuf(int magBuf);
};

