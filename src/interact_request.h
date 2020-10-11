#ifndef _INTERACT_REQUEST_H
#define _INTERACT_REQUEST_H

// #include "sprite.h"
// #include "item.h"
class Sprite;
class Item;

// `sprite` wants to use `item` to interact with the Tile at (`tileX`, `tileY`)
struct InteractRequest
{
    Sprite* sprite;
    Item* item;
    int tileX, tileY;
};

#endif