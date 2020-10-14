#include "inventory.h"

Inventory::Inventory()
{
    inventory = std::vector<std::shared_ptr<Item>>(
        5,
        std::shared_ptr<Item>()
    );
    selectedIndex = 0;
}

std::shared_ptr<Item> Inventory::getSelectedItem()
{
    return inventory[selectedIndex];
}

bool Inventory::checkIsFull()
{
    for (int i = 0; i < inventory.size(); i++)
    {
        if (!inventory[i])
        {
            return false;
        }
    }
    return true;
}

void Inventory::giveItem(std::shared_ptr<Item> item)
{
    int i = 0; 
    while (i < inventory.size())
    {
        if (!inventory[i])
        {
            inventory[i] = item;
            return;
        }
        i++;
    }
    throw std::runtime_error(
        "Can't add item: Inventory is full"
    );
}

void Inventory::rotateToNextItem()
{
    selectedIndex = (selectedIndex + 1) % inventory.size();
}
