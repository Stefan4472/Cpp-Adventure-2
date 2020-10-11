#ifndef _PICKAXE_ITEM_H
#define _PICKAXE_ITEM_H

#include "item.h"


class PickaxeItem : public Item
{
public:
    PickaxeItem();
    TextureId getTextureId();
    InteractType getInteractType();
};

#endif