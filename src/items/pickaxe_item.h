#ifndef _PICKAXE_ITEM_H
#define _PICKAXE_ITEM_H

#include "item.h"
// TODO: REMOVE
#include <iostream>

class PickaxeItem : public Item
{
public:
    PickaxeItem();
    TextureId getTextureId();
    bool isPlaceableAsTile();
    bool isPlaceableAsObject();
    void onFinishedInteract(ObjectType objectType);
};

#endif