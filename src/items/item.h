#ifndef _ITEM_H
#define _ITEM_H

#include "texture_id.h"
#include "item_type.h"
#include "interact_type.h"


class Item
{
public:
    Item(ItemType itemType);
    ItemType getItemType();
    virtual TextureId getTextureId() = 0;
    virtual InteractType getInteractType() = 0;

private:
    ItemType itemType;
};

#endif