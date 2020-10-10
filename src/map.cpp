#include "map.h"

Map::Map(std::vector<std::vector<std::shared_ptr<Tile>>> mapTiles)
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
    
    std::vector<std::vector<std::shared_ptr<Tile>>> map_tiles;
    std::string next_line;
    int curr_row = 0;
    int curr_col = 0;

    while (std::getline(map_file, next_line))
    {
        int next_val;
        std::stringstream str_stream(next_line);
        map_tiles.push_back(std::vector<std::shared_ptr<Tile>>());
     
        // Get each integer
        while (str_stream >> next_val)
        {
            map_tiles.back().push_back(TileFactory::createTile(
                resolveTileType(next_val),
                curr_col * TextureCache::TILE_SIZE_PX,
                curr_row * TextureCache::TILE_SIZE_PX
            ));
            curr_col++;
        }
        curr_row++;
        curr_col = 0;
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

bool Map::isTileWithinMap(int tileX, int tileY)
{
    return
        tileX >= 0 &&
        tileX < numCols &&
        tileY >= 0 &&
        tileY < numRows;
}

void Map::drawTiles(
        GameRenderer* gameRenderer,
        SDL_Rect& visibleWorld
) {
    // Calculate number of tiles needed to fill the screen.
    // Add two in each dimension to ensure the screen is always covered.
    int tiles_w = visibleWorld.w / TextureCache::TILE_SIZE_PX + 2;
    int tiles_h = visibleWorld.h / TextureCache::TILE_SIZE_PX + 2;
    
    int start_tile_x = visibleWorld.x / TextureCache::TILE_SIZE_PX - 1;
    int start_tile_y = visibleWorld.y / TextureCache::TILE_SIZE_PX - 1;
    
    // Draw tiles
    for (int i = 0; i < tiles_h; i++)
    {
        for (int j = 0; j < tiles_w; j++)
        {
            int tile_x = start_tile_x + j;
            int tile_y = start_tile_y + i;

            // Skip if out of range (special case)
            if (!isTileWithinMap(tile_x, tile_y))
            {
                continue;
            }

            mapTiles[tile_y][tile_x]->draw(gameRenderer);
        }
    }
}

bool Map::areTilesValid(
        std::vector<std::vector<std::shared_ptr<Tile>>> mapTiles
) {
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
    for (std::vector<std::shared_ptr<Tile>> tile_row : mapTiles)
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