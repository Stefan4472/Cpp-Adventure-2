#include "gravel_item.h"

GravelItem::GravelItem() : Item(ItemType::GRAVEL)
{

}

TextureId GravelItem::getTextureId()
{
    return TextureId::GRAVEL_ITEM;
}

InteractType GravelItem::getInteractType()
{
    return InteractType::OBJECT_ONLY;
}

void GravelItem::onFinishedInteract(ObjectType objectType)
{
    // TODO: INDICATE THAT WE'VE BEEN CONSUMED
}