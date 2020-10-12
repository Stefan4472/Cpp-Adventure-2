#ifndef _MAP_H
#define _MAP_H

#include <boost/filesystem.hpp>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "tile_factory.h"
#include "object_factory.h"
#include "game_renderer.h"
#include "game_context.h"
#include "sprite.h"


class Map
{
public:
    // TODO: ADD SPRITES TO MAP. DEFINED IN 'SPRITES.TXT' AND INITIALIZED
    // BASED ON TILE. THEN STORED IN A LIST OR HASHMAP.
    Map(
        GameContext* gameContext,
        std::vector<std::vector<std::shared_ptr<Tile>>> mapTiles,
        std::vector<std::vector<std::shared_ptr<MapObject>>> mapObjects
    );

    // Return size of world (x, y)
    std::pair<int, int> getSizePx();

    // Return whether the provided tile coordinate is valid
    bool isTileWithinMap(
        int tileX, 
        int tileY
    );
    // Return whether a sprite could walk on the specified tile
    bool isTileWalkable(
        int tileX, 
        int tileY
    );
    // Convert world coordinates to tile coordinates.
    // Throws runtime_error if coordinates are outside of world.
    std::pair<int, int> resolveTile(
        double worldX,
        double worldY
    );
    // Convert tile coordinates to world coordinates.
    // Throws runtime_error if tile coordinates are outside of world.
    SDL_Rect calcTileCoords(
        int tileX,
        int tileY
    );
    // Return Tile at specified coordinates
    std::shared_ptr<Tile> getTile(
        int tileX, 
        int tileY
    );
    // Return object at the specified tile coordinates.
    // May return an emtpy (NULL) pointer if there is no object
    // at those coordinates.
    std::shared_ptr<MapObject> getObjectAtTile(
        int tileX, 
        int tileY
    );
    // TODO
    std::shared_ptr<Sprite> getSpriteAtTile(
        int tileX, 
        int tileY
    );
    // NOTE: tile must be empty
    void createObjectAtTile(
        ObjectType objectType,
        int tileX,
        int tileY
    );
    void removeObjectAtTile(
        int tileX,
        int tileY
    );
    void replaceTile(
        TileType newTileType,
        int tileX,
        int tileY
    );

    void drawTiles(
        GameRenderer* gameRenderer,
        SDL_Rect& visibleWorld
    );

    // TODO: NEED TO PROPERLY LAYER OBJECTS WITH SPRITES, ITEMS, ETC.
    void drawObjects(
        GameRenderer* gameRenderer,
        SDL_Rect& visibleWorld
    );

    // Load map stored at the specified directory
    static Map loadMap(
        GameContext* gameContext,
        boost::filesystem::path dirPath
    );

private:
    int numRows, numCols;
    GameContext* gameContext;
    std::vector<std::vector<std::shared_ptr<Tile>>> mapTiles;
    std::vector<std::vector<std::shared_ptr<MapObject>>> mapObjects;

    static std::vector<std::vector<std::shared_ptr<Tile>>> loadTiles(
        GameContext* gameContext,
        boost::filesystem::path tilesPath
    );

    // TODO: WILL LIKELY NEED TO KNOW THE TILES, SO THAT IT CAN PROVIDE
    // TILE INFORMATION TO EACH OBJECT. FOR EXAMPLE, IF THE OBJECT IS ON
    // GRASS, IT MIGHT WANT TO USE A DIFFERENT TEXTURE THAN IF IT IS ON 
    // SAND. WE MAY ALSO WANT TO KNOW OTHER INFO, E.G., IS IT IN SNOW?
    static std::vector<std::vector<std::shared_ptr<MapObject>>> loadObjects(
        GameContext* gameContext,
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