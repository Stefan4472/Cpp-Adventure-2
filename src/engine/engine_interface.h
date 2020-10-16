#ifndef _ENGINE_INTERFACE_H
#define _ENGINE_INTERFACE_H

#include <memory>
class Tile;
class MapObject;
class Sprite;

/*
Interface implemented by the GameEngine. Provides various utility
functions.

Also avoids the circular includes of Tiles, MapObjects, etc. 
having direct access to code that includes them. 
*/
class EngineInterface
{
public:
    // Return whether the provided tile coordinate is valid
    virtual bool isTileWithinMap(
        int tileX, 
        int tileY
    ) = 0;

    virtual bool isTileWalkable(
        int tileX,
        int tileY
    ) = 0;

    virtual std::pair<int, int> resolveTile(
        double worldX, 
        double worldY
    ) = 0;

    // Get the coordinates of the tile the player is currently on
    virtual std::pair<int, int> getPlayerTile() = 0;
    
    // Generate and return a random integer between 1 and 100,
    // inclusive.  TODO: THIS IS VERY SIMPLE AT THE MOMENT.
    virtual int genRandInt1To100() = 0;


    // TODO: LOOKUPSPRITETILE(SPRITE*)

    // virtual std::shared_ptr<MapObject> getObjectAtTile(
    //     int tileX, 
    //     int tileY
    // ) = 0;

    // virtual std::shared_ptr<Tile> getTile(
    //     int tileX, 
    //     int tileY
    // ) = 0;

    // virtual std::shared_ptr<Sprite> getSprite(
    //     int spriteId
    // ) = 0;

    
};

#endif