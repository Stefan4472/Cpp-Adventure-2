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
    virtual InteractType getInteractType() = 0;
    // Called after successful interact.
    // By default does nothing.
    virtual void onFinishedInteract(TileType);
    virtual void onFinishedInteract(ObjectType);
    virtual void onFinishedInteract(SpriteType);

private:
    ItemType itemType;
};

#endif