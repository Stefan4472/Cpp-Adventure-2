#ifndef _MAP_H
#define _MAP_H

#include <boost/filesystem.hpp>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "tile_type.h"
#include "game_renderer.h"


class Map
{
public:
    Map(std::vector<std::vector<TileType>> mapTiles);

    static Map fromFile(boost::filesystem::path filePath);
    // Tile map  TODO: MAKE CONST?
    std::vector<std::vector<TileType>> mapTiles;
    int numRows, numCols;

    void draw(
        GameRenderer* gameRenderer,
        SDL_Rect& visibleWorld
    );

private:
    static bool areTilesValid(std::vector<std::vector<TileType>> mapTiles);
    // Convert integer read from map file to a `TileType` instance.
    static TileType resolveTileType(int tileId);
};

#endif