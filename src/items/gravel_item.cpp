#include "gravel_item.h"

GravelItem::GravelItem() : Item(ItemType::GRAVEL)
{

}

TextureId GravelItem::getTextureId()
{
    return TextureId::GRAVEL_ITEM;
}

bool GravelItem::isPlaceableAsTile()
{
    return true;
}

bool GravelItem::isPlaceableAsObject()
{
    return false;
}

TileType GravelItem::getTilePlaced()
{
    return TileType::STONE;
}


void GravelItem::onFinishedInteract(ObjectType objectType)
{
    // TODO: INDICATE THAT WE'VE BEEN CONSUMED
}