#include "item_factory.h"

std::shared_ptr<Item> ItemFactory::createItem(
        GameContext* gameContext,
        ItemType itemType
) {
    switch (itemType)
    {
        case ItemType::PICKAXE:
        {
            return std::make_shared<PickaxeItem>();
        }
        case ItemType::GRAVEL:
        {
            return std::make_shared<GravelItem>();
        }
        default:
        {
            throw std::invalid_argument(
                std::string("Unsupported itemType ") + 
                std::to_string(static_cast<int>(itemType))
            );
        }
    }
}