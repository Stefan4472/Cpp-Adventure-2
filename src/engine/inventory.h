#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <memory>
#include "item.h"

// For now, an Inventory is just a vector of 5 Items.
// There is also the "currItem", which is the one currently
// selected. Change selection using the provided methods.
class Inventory
{
public:
    Inventory();
    // (may return empty pointer)
    std::shared_ptr<Item> getSelectedItem();
    // NOTE: FOR NOW THIS IS O(N)
    bool checkIsFull();
    // NOTE: FOR NOW THIS IS O(N)
    // Raises exception if Inventory is full
    void giveItem(std::shared_ptr<Item> item);
    void rotateToNextItem();
private:
    std::vector<std::shared_ptr<Item>> inventory;
    int selectedIndex;
};

#endif