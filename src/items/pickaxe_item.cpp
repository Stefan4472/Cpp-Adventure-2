#include "pickaxe_item.h"

PickaxeItem::PickaxeItem() : Item(ItemType::PICKAXE)
{

}

TextureId PickaxeItem::getTextureId()
{
    return TextureId::PICKAXE_ITEM;
}

bool PickaxeItem::isPlaceableAsTile()
{
    return false;
}

bool PickaxeItem::isPlaceableAsObject()
{
    return false;
}

void PickaxeItem::onFinishedInteract(ObjectType objectType)
{
    std::cout << "Just finished interact with " << 
        static_cast<int>(objectType) << std::endl;
}