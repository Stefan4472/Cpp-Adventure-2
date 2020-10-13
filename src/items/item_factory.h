#ifndef _ITEM_FACTORY_H
#define _ITEM_FACTORY_H

#include <memory>
#include "item_type.h"
#include "game_context.h"
#include "pickaxe_item.h"
#include "gravel_item.h"

class ItemFactory
{
public:
    static std::shared_ptr<Item> createItem(
        GameContext* gameContext,
        ItemType itemType
    );
};
#endif