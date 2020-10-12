#include "item.h"

Item::Item(ItemType itemType)
{
    this->itemType = itemType;
}

ItemType Item::getItemType()
{
    return itemType;
}

void Item::onFinishedInteract(TileType)
{

}

void Item::onFinishedInteract(ObjectType)
{

}

void Item::onFinishedInteract(SpriteType)
{

}