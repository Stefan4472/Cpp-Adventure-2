#include "pickaxe_item.h"

PickaxeItem::PickaxeItem() : Item(ItemType::PICKAXE)
{

}

TextureId PickaxeItem::getTextureId()
{
    return TextureId::PICKAXE_ITEM;
}

InteractType PickaxeItem::getInteractType()
{
    return InteractType::OBJECT_ONLY;
}

void PickaxeItem::onFinishedInteract(ObjectType objectType)
{
    std::cout << "Just finished interact with " << 
        static_cast<int>(objectType) << std::endl;
}