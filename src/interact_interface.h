#ifndef _INTERACT_CONTEXT_H
#define _INTERACT_CONTEXT_H

#include "tile_type.h"
#include "item_type.h"
#include "object_type.h"


// Interface providing methods for entities to call during interactions.
class InteractInterface
{
public:
    // TODO: IMPROVE METHODS. WE PROBABLY WANT TO JUST PASS POINTERS OR IDS
    // NOTE: PASSING POINTERS WOULD REQUIRE US TO INCLUDE 'SPRITE', 'MAPOBJECT', ETC... PROBABLY NOT A GOOD IDEA AFTER ALL
    // virtual void changeTile(
    //     int tileX, 
    //     int tileY, 
    //     TileType newTileType
    // ) = 0;

    virtual void destroyObject(
        int tileX,
        int tileY
    ) = 0;

    // virtual void createDrop(
    //     int tileX,
    //     int tileY,
    //     ItemType itemType,
    //     int quantity
    // ) = 0;

    // virtual void killSprite(
    //     int tileX,
    //     int tileY
    // ) = 0;

    // virtual void createObject(
    //     int tileX,
    //     int tileY,
    //     ObjectType objectType
    // );
};
#endif