#ifndef _GRAVEL_ITEM_H
#define _GRAVEL_ITEM_H

#include "item.h"

// Placing this (for now) creates a StoneTile.
class GravelItem : public Item
{
public:
    GravelItem();
    TextureId getTextureId();
    bool isPlaceableAsTile();
    bool isPlaceableAsObject();
    TileType getTilePlaced();
    void onFinishedInteract(ObjectType objectType);
};

#endif