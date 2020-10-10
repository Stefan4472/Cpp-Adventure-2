#ifndef _MAP_H
#define _MAP_H

#include <boost/filesystem.hpp>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "tile_type.h"
#include "tile_factory.h"
#include "game_renderer.h"


class Map
{
public:
    Map(std::vector<std::vector<std::shared_ptr<Tile>>> mapTiles);

    static Map fromFile(boost::filesystem::path filePath);

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

    static bool areTilesValid(
        std::vector<std::vector<std::shared_ptr<Tile>>> mapTiles
    );

    // Convert integer read from map file to a `TileType` instance.
    static TileType resolveTileType(int tileId);
};

#endif