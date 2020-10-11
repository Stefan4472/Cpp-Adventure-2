#ifndef _MAP_H
#define _MAP_H

#include <boost/filesystem.hpp>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "tile_factory.h"
#include "object_factory.h"
#include "game_renderer.h"


class Map
{
public:
    // TODO: ADD SPRITES TO MAP. DEFINED IN 'SPRITES.TXT' AND INITIALIZED
    // BASED ON TILE. THEN STORED IN A LIST OR HASHMAP.
    Map(
        std::vector<std::vector<std::shared_ptr<Tile>>> mapTiles,
        std::vector<std::vector<std::shared_ptr<MapObject>>> mapObjects
    );

    // Load map stored at the specified directory
    static Map loadMap(boost::filesystem::path dirPath);

    // Return size of world (x, y)
    std::pair<int, int> getSizePx();

    // Return whether the provided tile coordinate is valid
    bool isTileWithinMap(int tileX, int tileY);

    std::shared_ptr<MapObject> getObjectAtTile(int tileX, int tileY);
    
    void drawTiles(
        GameRenderer* gameRenderer,
        SDL_Rect& visibleWorld
    );

    // TODO: NEED TO PROPERLY LAYER OBJECTS WITH SPRITES, ITEMS, ETC.
    void drawObjects(
        GameRenderer* gameRenderer,
        SDL_Rect& visibleWorld
    );

private:
    int numRows, numCols;
    std::vector<std::vector<std::shared_ptr<Tile>>> mapTiles;
    std::vector<std::vector<std::shared_ptr<MapObject>>> mapObjects;

    static std::vector<std::vector<std::shared_ptr<Tile>>> loadTiles(
        boost::filesystem::path tilesPath
    );

    // TODO: WILL LIKELY NEED TO KNOW THE TILES, SO THAT IT CAN PROVIDE
    // TILE INFORMATION TO EACH OBJECT. FOR EXAMPLE, IF THE OBJECT IS ON
    // GRASS, IT MIGHT WANT TO USE A DIFFERENT TEXTURE THAN IF IT IS ON 
    // SAND. WE MAY ALSO WANT TO KNOW OTHER INFO, E.G., IS IT IN SNOW?
    static std::vector<std::vector<std::shared_ptr<MapObject>>> loadObjects(
        boost::filesystem::path objectsPath
    );

    // Throws runtime_error
    static void checkMapValidity(
        std::vector<std::vector<std::shared_ptr<Tile>>> mapTiles,
        std::vector<std::vector<std::shared_ptr<MapObject>>> mapObjects
    );

    // Convert integer read from map file to a `TileType` instance.
    static TileType resolveTileType(int tileId);
    // Convert integer read from map file to an `ObjectType` instance.
    static ObjectType resolveObjectType(int objectId);
};

#endif