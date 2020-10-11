#include "item.h"

Item::Item(ItemType itemType)
{
    this->itemType = itemType;
}

ItemType Item::getItemType()
{
    return itemType;
}
