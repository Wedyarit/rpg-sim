#pragma once

#include "Item.h"
#include <fstream>

class Inventory {
    Item items[4];

public:
    explicit Inventory(std::istream &f);

    Item *getItems();

    Inventory();
};