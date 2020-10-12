#ifndef _ITEM_H
#define _ITEM_H

#include "texture_id.h"
#include "item_type.h"
#include "interact_type.h"
#include "sprite_type.h"
#include "object_type.h"
#include "tile_type.h"


class Item
{
public:
    Item(ItemType itemType);
    ItemType getItemType();
    virtual TextureId getTextureId() = 0;
    
    // virtual bool wasConsumed();  TODO?

    // TODO: PROPERTIES SHOULD REALLY BE SET AS VARIABLES, NOT AS FUNCTIONS

    // Is this item placeable?
    // As in, does an interact cause a new Tile or
    // MapObject to be placed?
    virtual bool isPlaceableAsTile() = 0;
    virtual bool isPlaceableAsObject() = 0;
    // By default, throw std::runtime_error() unless overloaded.
    // Call the corresponding `isPlaceable()` method before using.
    virtual TileType getTilePlaced();
    virtual ObjectType getObjectPlaced();

    // Called after successful interact.
    // By default does nothing.
    virtual void onFinishedInteract(TileType);
    virtual void onFinishedInteract(ObjectType);
    virtual void onFinishedInteract(SpriteType);

private:
    ItemType itemType;
};

#endif