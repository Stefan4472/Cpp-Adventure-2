#ifndef _MAP_H
#define _MAP_H

#include <boost/filesystem.hpp>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "tile_type.h"
#include "tile_factory.h"
#include "map_object.h"
#include "game_renderer.h"


class Map
{
public:
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

    void drawTiles(
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
};

#endif