#include "item.h"

Item::Item(ItemType itemType)
{
    this->itemType = itemType;
}

ItemType Item::getItemType()
{
    return itemType;
}

TileType Item::getTilePlaced()
{
    throw std::runtime_error("This Item does not place an Item");
}

ObjectType Item::getObjectPlaced()
{
    throw std::runtime_error("This Item does not place an Object");
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