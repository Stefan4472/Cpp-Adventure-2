#ifndef _MAP_H
#define _MAP_H

#include <boost/filesystem.hpp>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <stdexcept>
#include "tile_factory.h"
#include "object_factory.h"
#include "item_factory.h"
#include "actor_factory.h"
#include "game_renderer.h"
#include "game_context.h"
#include "engine_requests.h"
#include "drop.h"


class Map
{
public:
    Map(
        GameContext* gameContext,
        std::vector<std::vector<std::shared_ptr<Tile>>> tiles,
        std::vector<std::vector<std::shared_ptr<MapObject>>> mapObjects,
        std::vector<std::vector<std::shared_ptr<Drop>>> drops,
        std::vector<std::vector<std::shared_ptr<Actor>>> actors
    );

    // Return ref to the PlayerActor
    std::shared_ptr<PlayerActor> getPlayerActor();

    // Return size of world (x, y) (pixels)
    std::pair<int, int> getSizePx();

    // Return whether the provided tile coordinate is in the world.
    bool isTileWithinMap(
        int tileX, 
        int tileY
    );
    // Return whether a sprite could walk on the specified 
    // tile coordinates. Checks both the Tile at that coordinate,
    // as well as the MapObject (if any) at that coordinate.
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
    // Sprite requests to move to the specified tile.
    // Return whether this is allowed (i.e., tile is walkable).
    // This will also ensure two sprites can't move onto the
    // same tile during a single game update.
    bool requestMoveToTile(
        Sprite* sprite,
        int currTileX, 
        int currTileY,
        int newTileX, 
        int newTileY
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
    // Replace the tile at (tileX, tileY) with a new 
    // one of `newTileType`
    void replaceTile(
        TileType newTileType,
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
    // Check whether a MapObject can be created at the specified
    // tile coordinates. Makes sure that there isn't already a
    // MapObject there. 
    bool canCreateObjectAtTile(
        int tileX,
        int tileY
    );
    // Creates a new MapObject of `objectType` at the specified
    // tile coordinates. Throws `std::runtime_error` if a MapObject
    // of the specified type cannot be created at those coordinates.
    // Call `canCreateObjectAtTile()` first.
    void createObjectAtTile(
        ObjectType objectType,
        int tileX,
        int tileY
    );
    // Removes the MapObject (if any) at the specified tile 
    // coordinates.
    void removeObjectAtTile(
        int tileX,
        int tileY
    );
    // Return the Sprite (if any) currently at the specified
    // tile coordinates.
    std::shared_ptr<Sprite> getSpriteAtTile(
        int tileX,
        int tileY
    );
    // Removes the Sprite (if any) at the specified tile 
    // coordinates.
    void removeSpriteAtTile(
        int tileX,
        int tileY
    );
    // Creates a Drop containing the provided Item at the specified
    // tile coordinates.
    // TODO: PROVIDE AN ALTERNATE METHOD THAT CREATES THE ITEM *AND*
    // THE DROP
    void createDropAtTile(
        std::shared_ptr<Item> itemToDrop,
        int tileX,
        int tileY
    );
    // Return the Drop at the specified tile coordinates. May
    // be null.
    std::shared_ptr<Drop> getDropAtTile(
        int tileX,
        int tileY
    );
    // Remove the Drop (but not the Item it contains) at the
    // specified tile coordinates.
    void removeDropAtTile(
        int tileX,
        int tileY
    );
    // Looks up the Actor that the specified Sprite belongs to.
    // Note: currently very slow (TODO)
    std::shared_ptr<Actor> lookupSpriteActor(
        Sprite* sprite
    );

    // Update *everything*
    void update(UpdateContext& updateContext);

    // Draw the tiles to the provided `GameRenderer`. 
    // `visibleWorld` specifies the clip of world coordinates 
    // that are on-screen.
    void drawTiles(
        GameRenderer* gameRenderer,
        SDL_Rect& visibleWorld
    );
    // Draw the MapObject *and Drops* to the provided `GameRenderer`.
    // `visibleWorld` specifies the clip of world coordinates 
    // that are on-screen.
    // TODO: NEED TO PROPERLY LAYER OBJECTS WITH SPRITES, ITEMS, ETC.
    void drawObjects(
        GameRenderer* gameRenderer,
        SDL_Rect& visibleWorld
    );

    void drawSprites(
        GameRenderer* gameRenderer,
        SDL_Rect& visibleWorld
    );

    // Load map stored at the specified directory and return
    // created `Map` instance.
    static Map loadMap(
        GameContext* gameContext,
        boost::filesystem::path dirPath
    );

private:
    int numRows, numCols;
    GameContext* gameContext;
    std::vector<std::vector<std::shared_ptr<Tile>>> tiles;
    std::vector<std::vector<std::shared_ptr<MapObject>>> mapObjects;
    std::vector<std::vector<std::shared_ptr<Drop>>> drops;
    std::vector<std::vector<std::shared_ptr<Actor>>> actors;
    std::shared_ptr<PlayerActor> playerActor;

    // Store mapping of SpriteID to 'MoveToTileRequest'
    std::unordered_map<SpriteID, MoveToTileRequest> moveTileRequests;

    // Grid caching which tiles are walkable. 
    // std::vector<std::vector<bool>> walkableTiles;

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

    static std::vector<std::vector<std::shared_ptr<Drop>>> loadDrops(
        GameContext* gameContext,
        boost::filesystem::path objectsPath
    );

    static std::vector<std::vector<std::shared_ptr<Actor>>> loadActors(
        GameContext* gameContext,
        boost::filesystem::path spritesPath
    );

    // Throws runtime_error
    static void checkMapValidity(
        std::vector<std::vector<std::shared_ptr<Tile>>> tiles,
        std::vector<std::vector<std::shared_ptr<MapObject>>> mapObjects,
        std::vector<std::vector<std::shared_ptr<Drop>>> drops,
        std::vector<std::vector<std::shared_ptr<Actor>>> actors
    );

    // Convert integer read from map file to a `TileType` instance.
    static TileType resolveTileType(int tileId);
    // Convert integer read from map file to an `ObjectType` instance.
    static ObjectType resolveObjectType(int objectId);
    // Convert integer read from map file to an `ItemType` instance.
    static ItemType resolveItemType(int itemId);
    // Convert integer read from map file to a `SpriteType` instance.
    static SpriteType resolveSpriteType(int spriteId);
};

#endif