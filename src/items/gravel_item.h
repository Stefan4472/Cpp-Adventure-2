#ifndef _GRAVEL_ITEM_H
#define _GRAVEL_ITEM_H

#include "item.h"

class GravelItem : public Item
{
public:
    GravelItem();
    TextureId getTextureId();
    InteractType getInteractType();
    void onFinishedInteract(ObjectType objectType);
};

#endif