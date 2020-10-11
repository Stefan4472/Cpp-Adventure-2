#ifndef _ITEM_H
#define _ITEM_H

#include "texture_id.h"
#include "item_type.h"


class Item
{
public:
    Item(ItemType itemType);
    virtual TextureId getTextureId() = 0;

private:
    ItemType itemType;
};

#endif