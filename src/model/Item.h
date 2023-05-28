#pragma once

#include <string>

class Item {
    std::string name, description;
    int hpHeal, mpHeal, defBuf, atkBuf, magBuf, quantity;

public:
    const std::string &getName() const;
    void setName(const std::string &name);

    const std::string &getDescription() const;
    void setDescription(const std::string &description);

    int getHpHeal() const;
    void setHpHeal(int hpHeal);

    int getMpHeal() const;
    void setMpHeal(int mpHeal);

    int getDefBuf() const;
    void setDefBuf(int defBuf);

    int getAtkBuf() const;
    void setAtkBuf(int atkBuf);

    int getMagBuf() const;
    void setMagBuf(int magBuf);

    int getQuantity() const;
    void setQuantity(int quantity);
};