#include "map.h"

Map::Map(std::vector<std::vector<TileType>> mapTiles)
{
    if (!areTilesValid(mapTiles))
    {
        throw std::invalid_argument("Map tiles are invalid");
    }
    this->mapTiles = mapTiles;
    numRows = this->mapTiles.size();
    numCols = this->mapTiles[0].size();
}

// Static method
Map Map::fromFile(boost::filesystem::path filePath)
{
    std::ifstream map_file(filePath.string());
    if (!map_file.is_open())
    {
        throw std::runtime_error("Couldn't open map file");
    }
    
    std::vector<std::vector<TileType>> map_tiles;
    std::vector<TileType> next_map_row;
    std::string next_line;

    while (std::getline(map_file, next_line))
    {
        int next_val;
        std::stringstream str_stream(next_line);
        next_map_row.clear();
     
        // Get each integer
        while (str_stream >> next_val)
        {
            next_map_row.push_back(resolveTileType(next_val));
        }
        map_tiles.push_back(next_map_row);
    }

    map_file.close();
    return Map(map_tiles);
}

std::pair<int, int> Map::getSizePx()
{
    return std::make_pair(
        numCols * TextureCache::TILE_SIZE_PX,
        numRows * TextureCache::TILE_SIZE_PX
    );
}

void Map::drawTiles(
        GameRenderer* gameRenderer,
        SDL_Rect& visibleWorld
) {
    int tiles_w = visibleWorld.w / TextureCache::TILE_SIZE_PX + 1;
    int tiles_h = visibleWorld.h / TextureCache::TILE_SIZE_PX + 1;
    int start_tile_x = visibleWorld.x / TextureCache::TILE_SIZE_PX;
    int start_tile_y = visibleWorld.y / TextureCache::TILE_SIZE_PX;
    int offset_x = visibleWorld.x % TextureCache::TILE_SIZE_PX;
    int offset_y = visibleWorld.y % TextureCache::TILE_SIZE_PX;
    
    // Draw tiles
    for (int i = 0; i < tiles_h; i++)
    {
        for (int j = 0; j < tiles_w; j++)
        {
            int tile_x = start_tile_x + j;
            int tile_y = start_tile_y + i;

            // Skip if out of range (special case)
            if (tile_x < 0 || tile_x >= numCols || tile_y < 0 || tile_y >= numRows)
            {
                continue;
            }

            TileType tile = mapTiles[tile_y][tile_x];
            
            gameRenderer->drawToWorld(
                getTileTextureId(tile),
                visibleWorld.x - offset_x + j * TextureCache::TILE_SIZE_PX,
                visibleWorld.y - offset_y + i * TextureCache::TILE_SIZE_PX
            );
        }
    }
}

bool Map::areTilesValid(std::vector<std::vector<TileType>> mapTiles)
{
    // Make sure `mapTiles` is non-empty
    if (mapTiles.empty())
    {
        return false;
    }
    if (mapTiles[0].empty())
    {
        return false;
    }

    // Make sure each row has the same number of elements 
    int num_cols = mapTiles[0].size();
    for (std::vector<TileType> tile_row : mapTiles)
    {
        if (tile_row.size() != num_cols)
        {
            return false;
        }
    }

    return true;
}

TileType Map::resolveTileType(int tileId)
{
    switch (tileId)
    {
        case 1:
        {
            return TileType::GRASS;
        }
        case 2:
        {
            return TileType::SAND;
        }
        case 3:
        {
            return TileType::DIRT;
        }
        case 4:
        {
            return TileType::STONE;
        }
        default:
        {
            throw std::invalid_argument(
                std::string("Unsupported tile ID ") + std::to_string(tileId)
            );
        }
    }
}