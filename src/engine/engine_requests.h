#ifndef _INTERACT_REQUEST_H
#define _INTERACT_REQUEST_H


// TODO: RENAME TO `ENGINE_REQUEST`, AND PUT ALL REQUEST STRUCTS HERE?

#include "object_type.h"
#include "sprite_type.h"
#include "item_type.h"
#include "tile_type.h"

class Sprite;
class Item;

// `sprite` wants to use `item` to interact with the Tile at (`tileX`, `tileY`)
struct InteractRequest
{
    Sprite* sprite;
    Item* item;
    int tileX;
    int tileY;
};

// struct CreateSpriteRequest
// {
        // SpriteType spriteType;
        // int tileX, tileY;
// };

// struct DestroySpriteRequest
// {
        // int tileX, tileY;
// };

// TODO: NEED TO AVOID CIRCULAR INCLUDES. 
// THIS FILE IS INCLUDED BY `UpdateContext`, which all Sprites/Objects/Tiles get
struct CreateObjectRequest
{
    ObjectType objectType;
    int tileX;
    int tileY;
};

struct DestroyObjectRequest
{
    int tileX;
    int tileY;
};

struct ReplaceTileRequest
{
    TileType tileType;
    int tileX;
    int tileY;
};

struct CreateDropRequest
{
    ItemType itemType;
    int quantity;
    int tileX;
    int tileY;
};

// Represents a sprite's request to move to the specified
// new tile, imminently.
struct MoveToTileRequest
{
    Sprite* sprite;
    int currTileX, currTileY;
    int newTileX, newTileY;
};

#endif