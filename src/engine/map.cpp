#include "map.h"

Map::Map(
        GameContext* gameContext,
        std::vector<std::vector<std::shared_ptr<Tile>>> tiles,
        std::vector<std::vector<std::shared_ptr<MapObject>>> mapObjects,
        std::vector<std::vector<std::shared_ptr<Drop>>> drops,
        std::vector<std::vector<std::shared_ptr<Sprite>>> sprites
) {
    checkMapValidity(tiles, mapObjects, drops, sprites);
    this->gameContext = gameContext;
    this->tiles = tiles;
    this->mapObjects = mapObjects;
    this->drops = drops;
    this->sprites = sprites;

    numRows = this->tiles.size();
    numCols = this->tiles[0].size();

    // Find reference to the PlayerSprite.
    // `checkMapValidity()` will have ensured there is exactly one.
    for (auto row : sprites)
    {
        for (auto sprite : row)
        {
            if (sprite && sprite->getSpriteType() == SpriteType::PLAYER)
            {
                playerSprite = std::dynamic_pointer_cast<PlayerSprite>(
                    sprite
                );
            }
        }
    }
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

bool Map::isTileWalkable(int tileX, int tileY)
{
    // Check bounds
    if (!isTileWithinMap(tileX, tileY))
    {
        return false;
    }
    // Get object (if any) on desired tile
    std::shared_ptr<MapObject> object_on_tile =
        getObjectAtTile(tileX, tileY);
    // Check if object exists and isn't walkable
    if (object_on_tile && !object_on_tile->getIsWalkable())
    {
        return false;
    }
    // Otherwise, we're good!
    return true;
}

std::pair<int, int> Map::resolveTile(double worldX, double worldY)
{
    return std::make_pair(
        static_cast<int>(worldX) / TextureCache::TILE_SIZE_PX,
        static_cast<int>(worldY) / TextureCache::TILE_SIZE_PX
    );
}

SDL_Rect Map::calcTileCoords(int tileX, int tileY) 
{
    if (isTileWithinMap(tileX, tileY))
    {
        return SDL_Rect{
            tileX * TextureCache::TILE_SIZE_PX,
            tileY * TextureCache::TILE_SIZE_PX,
            TextureCache::TILE_SIZE_PX,
            TextureCache::TILE_SIZE_PX
        };
    }
    else
    {
        throw std::invalid_argument(
            "Tile coordinates out of bounds"
        );
    }
}

std::shared_ptr<Tile> Map::getTile(int tileX, int tileY)
{
    if (isTileWithinMap(tileX, tileY))
    {
        return tiles[tileY][tileX];
    }
    else
    {
        throw std::invalid_argument(
            "Tile coordinates out of bounds"
        );
    }
}

void Map::replaceTile(
        TileType newTileType,
        int tileX,
        int tileY
) {
    if (isTileWithinMap(tileX, tileY))
    {
        tiles[tileY][tileX].reset();

        SDL_Rect tile_coords = calcTileCoords(
            tileX, 
            tileY
        );

        tiles[tileY][tileX] = TileFactory::createTile(
            gameContext,
            newTileType,
            tile_coords
        );
    }
    else
    {
        throw std::invalid_argument(
            "Tile coordinates out of bounds"
        );
    }
}

std::shared_ptr<MapObject> Map::getObjectAtTile(int tileX, int tileY)
{
    if (isTileWithinMap(tileX, tileY))
    {
        return mapObjects[tileY][tileX];
    }
    else
    {
        throw std::invalid_argument(
            "Tile coordinates out of bounds"
        );
    }
}

bool Map::canCreateObjectAtTile(
        int tileX,
        int tileY
) {
    // Make sure tile is within bounds, and no object is currently there
    return 
        isTileWithinMap(tileX, tileY) && 
        !mapObjects[tileY][tileX];
}

void Map::createObjectAtTile(
        ObjectType objectType,
        int tileX,
        int tileY
) {
    if (canCreateObjectAtTile(tileX, tileY))
    {
        mapObjects[tileY][tileX] = ObjectFactory::createObject(
            gameContext,
            objectType,
            calcTileCoords(tileX, tileY)
        );
    }
    else
    {
        throw std::invalid_argument(
            "Can't put an object there: either the tile coordinates are "
            "out of bounds, or there is already an object there"
        );
    }
}

void Map::removeObjectAtTile(
        int tileX,
        int tileY
) {
    // TODO: MAKE SURE THERE ARE NO MEMORY LEAKS
    if (isTileWithinMap(tileX, tileY))
    {
        mapObjects[tileY][tileX].reset();
    }
    else
    {
        throw std::invalid_argument(
            "Tile coordinates out of bounds"
        );
    }
}

std::shared_ptr<Sprite> Map::getSpriteAtTile(int tileX, int tileY)
{
    // TODO: IMPLEMENT
    throw std::runtime_error(
        "Unimplemented"
    );
    // return std::shared_ptr<Sprite>();
}

void Map::createDropAtTile(
        std::shared_ptr<Item> itemToDrop,
        int tileX,
        int tileY
) {
    // TODO: CHECK IF ALREADY EXISTS HERE?
    if (isTileWithinMap(tileX, tileY))
    {
        drops[tileY][tileX].reset();
        drops[tileY][tileX] = std::make_shared<Drop>(
            gameContext,
            itemToDrop,
            calcTileCoords(tileX, tileY)
        );
    }
    else
    {
        throw std::invalid_argument(
            "Tile coordinates out of bounds"
        );
    }

}
    
std::shared_ptr<Drop> Map::getDropAtTile(
        int tileX,
        int tileY
) {
    if (isTileWithinMap(tileX, tileY))
    {
        return drops[tileY][tileX];
    }
    else
    {
        throw std::invalid_argument(
            "Tile coordinates out of bounds"
        );
    }
}

void Map::removeDropAtTile(
        int tileX,
        int tileY
) {
    if (isTileWithinMap(tileX, tileY))
    {
        drops[tileY][tileX].reset();
    }
    else
    {
        throw std::invalid_argument(
            "Tile coordinates out of bounds"
        );
    }
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

            tiles[tile_y][tile_x]->draw(gameRenderer);
        }
    }
}

void Map::drawObjects(
        GameRenderer* gameRenderer,
        SDL_Rect& visibleWorld
) {
    // Calculate number of tiles needed to fill the screen.
    // Add two in each dimension to ensure the screen is always covered.
    int tiles_w = visibleWorld.w / TextureCache::TILE_SIZE_PX + 2;
    int tiles_h = visibleWorld.h / TextureCache::TILE_SIZE_PX + 2;
    
    int start_tile_x = visibleWorld.x / TextureCache::TILE_SIZE_PX - 1;
    int start_tile_y = visibleWorld.y / TextureCache::TILE_SIZE_PX - 1;
    
    // Draw objects (and Drops)
    for (int i = 0; i < tiles_h; i++)
    {
        for (int j = 0; j < tiles_w; j++)
        {
            int tile_x = start_tile_x + j;
            int tile_y = start_tile_y + i;

            // Skip if out of range (special case, occurs close to
            // map bounds)
            if (!isTileWithinMap(tile_x, tile_y))
            {
                continue;
            }
            // Draw MapObject at tile, if one exists
            if (mapObjects[tile_y][tile_x])
            {
                mapObjects[tile_y][tile_x]->draw(gameRenderer);
            }
            // Draw Drop at tile, if one exists
            if (drops[tile_y][tile_x])
            {
                drops[tile_y][tile_x]->draw(gameRenderer);
            }
        }
    }
}

void Map::drawSprites(
        GameRenderer* gameRenderer,
        SDL_Rect& visibleWorld
) {
    // Calculate number of tiles needed to fill the screen.
    // Add two in each dimension to ensure the screen is always covered.
    int tiles_w = visibleWorld.w / TextureCache::TILE_SIZE_PX + 2;
    int tiles_h = visibleWorld.h / TextureCache::TILE_SIZE_PX + 2;
    
    int start_tile_x = visibleWorld.x / TextureCache::TILE_SIZE_PX - 1;
    int start_tile_y = visibleWorld.y / TextureCache::TILE_SIZE_PX - 1;
    
    // Draw sprites
    for (int i = 0; i < tiles_h; i++)
    {
        for (int j = 0; j < tiles_w; j++)
        {
            int tile_x = start_tile_x + j;
            int tile_y = start_tile_y + i;

            // Skip if out of range (special case, occurs close to
            // map bounds)
            if (!isTileWithinMap(tile_x, tile_y))
            {
                continue;
            }
            // Draw Sprite at tile, if one exists
            if (sprites[tile_y][tile_x])
            {
                sprites[tile_y][tile_x]->draw(gameRenderer);
            }
        }
    }
}

// Static method
Map Map::loadMap(
        GameContext* gameContext,
        boost::filesystem::path dirPath
) {
    if (!boost::filesystem::is_directory(dirPath))
    {
        throw std::invalid_argument(
            "The provided path is not a directory"
        );
    }

    auto map_tiles = loadTiles(
        gameContext, 
        dirPath / "tiles.txt"
    );
    auto map_objects = loadObjects(
        gameContext, 
        dirPath / "objects.txt"
    );
    auto map_drops = loadDrops(
        gameContext,
        dirPath / "drops.txt"
    );
    auto map_sprites = loadSprites(
        gameContext,
        dirPath / "sprites.txt"
    );

    return Map(
        gameContext,
        map_tiles, 
        map_objects,
        map_drops,
        map_sprites
    );
}

std::vector<std::vector<std::shared_ptr<Tile>>> Map::loadTiles(
        GameContext* gameContext,
        boost::filesystem::path tilesPath
) {
    std::ifstream tiles_file(tilesPath.string());
    if (!tiles_file.is_open())
    {
        throw std::runtime_error(
            std::string("Couldn't open map tiles file '") +
            tilesPath.string() + "')"
        );
    }
    
    std::vector<std::vector<std::shared_ptr<Tile>>> map_tiles;
    std::string next_line;
    int curr_row = 0;
    int curr_col = 0;

    while (std::getline(tiles_file, next_line))
    {
        int next_val;
        std::stringstream str_stream(next_line);
        map_tiles.push_back(std::vector<std::shared_ptr<Tile>>());
     
        // Get each integer
        while (str_stream >> next_val)
        {
            SDL_Rect tile_coords = {
                curr_col * TextureCache::TILE_SIZE_PX,
                curr_row * TextureCache::TILE_SIZE_PX,
                TextureCache::TILE_SIZE_PX,
                TextureCache::TILE_SIZE_PX
            };

            map_tiles.back().push_back(TileFactory::createTile(
                gameContext,
                resolveTileType(next_val),
                tile_coords
            ));
            curr_col++;
        }
        curr_row++;
        curr_col = 0;
    }

    tiles_file.close();
    return map_tiles;
}

std::vector<std::vector<std::shared_ptr<MapObject>>> Map::loadObjects(
        GameContext* gameContext,
        boost::filesystem::path objectsPath
) {
    std::ifstream objects_file(objectsPath.string());
    if (!objects_file.is_open())
    {
        throw std::runtime_error(
            std::string("Couldn't open map objects file '") +
            objectsPath.string() + "')"
        );
    }
    
    std::vector<std::vector<std::shared_ptr<MapObject>>> map_objects;
    std::string next_line;
    int curr_row = 0;
    int curr_col = 0;

    while (std::getline(objects_file, next_line))
    {
        int next_val;
        std::stringstream str_stream(next_line);
        map_objects.push_back(std::vector<std::shared_ptr<MapObject>>());
     
        // Get each integer
        while (str_stream >> next_val)
        {
            if (next_val)
            {
                SDL_Rect base_tile = {
                    curr_col * TextureCache::TILE_SIZE_PX,
                    curr_row * TextureCache::TILE_SIZE_PX,
                    TextureCache::TILE_SIZE_PX,
                    TextureCache::TILE_SIZE_PX
                };

                map_objects.back().push_back(ObjectFactory::createObject(
                    gameContext,
                    resolveObjectType(next_val),
                    base_tile
                ));
            }
            else
            {
                // Push empty pointer
                map_objects.back().push_back(
                    std::shared_ptr<MapObject>()
                );
            }
            curr_col++;
        }

        curr_row++;
        curr_col = 0;
    }

    objects_file.close();
    return map_objects;
}

std::vector<std::vector<std::shared_ptr<Drop>>> Map::loadDrops(
        GameContext* gameContext,
        boost::filesystem::path objectsPath
) {
    std::ifstream drops_file(objectsPath.string());
    if (!drops_file.is_open())
    {
        throw std::runtime_error(
            std::string("Couldn't open map drops file '") +
            objectsPath.string() + "')"
        );
    }
    
    std::vector<std::vector<std::shared_ptr<Drop>>> map_drops;
    std::string next_line;
    int curr_row = 0;
    int curr_col = 0;

    while (std::getline(drops_file, next_line))
    {
        int next_val;
        std::stringstream str_stream(next_line);
        map_drops.push_back(std::vector<std::shared_ptr<Drop>>());
     
        // Get each integer
        while (str_stream >> next_val)
        {
            if (next_val)
            {
                auto dropped_item = ItemFactory::createItem(
                    gameContext,
                    resolveItemType(next_val)
                );
            
                SDL_Rect base_tile = {
                    curr_col * TextureCache::TILE_SIZE_PX,
                    curr_row * TextureCache::TILE_SIZE_PX,
                    TextureCache::TILE_SIZE_PX,
                    TextureCache::TILE_SIZE_PX
                };

                map_drops.back().push_back(std::make_shared<Drop>(
                    gameContext,
                    dropped_item,
                    base_tile
                ));
            }
            else
            {
                // Push empty pointer
                map_drops.back().push_back(
                    std::shared_ptr<Drop>()
                );
            }
            curr_col++;
        }

        curr_row++;
        curr_col = 0;
    }

    drops_file.close();
    return map_drops;
}

std::vector<std::vector<std::shared_ptr<Sprite>>> Map::loadSprites(
        GameContext* gameContext,
        boost::filesystem::path spritesPath
) {
    std::ifstream sprites_file(spritesPath.string());
    if (!sprites_file.is_open())
    {
        throw std::runtime_error(
            std::string("Couldn't open map sprites file '") +
            spritesPath.string() + "')"
        );
    }
    
    std::vector<std::vector<std::shared_ptr<Sprite>>> map_sprites;
    std::string next_line;
    int curr_row = 0;
    int curr_col = 0;

    while (std::getline(sprites_file, next_line))
    {
        int next_val;
        std::stringstream str_stream(next_line);
        map_sprites.push_back(std::vector<std::shared_ptr<Sprite>>());
     
        // Get each integer
        while (str_stream >> next_val)
        {
            if (next_val)
            {
                SDL_Rect base_tile = {
                    curr_col * TextureCache::TILE_SIZE_PX,
                    curr_row * TextureCache::TILE_SIZE_PX,
                    TextureCache::TILE_SIZE_PX,
                    TextureCache::TILE_SIZE_PX
                };

                map_sprites.back().push_back(SpriteFactory::createSprite(
                    gameContext,
                    resolveSpriteType(next_val),
                    base_tile
                ));
            }
            else
            {
                // Push empty pointer
                map_sprites.back().push_back(
                    std::shared_ptr<Sprite>()
                );
            }
            curr_col++;
        }

        curr_row++;
        curr_col = 0;
    }

    sprites_file.close();
    return map_sprites;
}

void Map::checkMapValidity(
        std::vector<std::vector<std::shared_ptr<Tile>>> tiles,
        std::vector<std::vector<std::shared_ptr<MapObject>>> mapObjects,
        std::vector<std::vector<std::shared_ptr<Drop>>> drops,
        std::vector<std::vector<std::shared_ptr<Sprite>>> sprites
) {
    // Make sure `tiles` is non-empty
    if (tiles.empty())
    {
        throw std::invalid_argument(
            "The provided `tiles` is empty"
        );
    }
    if (tiles[0].empty())
    {
        throw std::invalid_argument(
            "The provided `tiles` first row is empty"
        );
    }

    // Make sure each row has the same number of elements 
    int num_cols = tiles[0].size();
    int curr_row = 0;
    for (std::vector<std::shared_ptr<Tile>> tile_row : tiles)
    {
        if (tile_row.size() != num_cols)
        {
            throw std::invalid_argument(
                std::string("Non-uniform number of columns in row ") +
                std::to_string(curr_row)
            );
        }
        curr_row++;
    }

    // Make sure `mapObjects` is the same size as `tiles`
    if (mapObjects.size() != tiles.size())
    {
        throw std::invalid_argument(
            "`mapObjects` does not have the same number of rows as `tiles`"
        );
    }
    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i].size() != mapObjects[i].size())
        {
            throw std::invalid_argument(
                std::string("`mapObjects` does not have the same number of columns as `tiles` (row ") +
                std::to_string(curr_row) + ")"
            );
        }
    }

    // Make sure `drops` is the same size as `tiles`
    if (drops.size() != tiles.size())
    {
        throw std::invalid_argument(
            "`drops` does not have the same number of rows as `tiles`"
        );
    }
    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i].size() != drops[i].size())
        {
            throw std::invalid_argument(
                std::string("`drops` does not have the same number of columns as `tiles` (row ") +
                std::to_string(curr_row) + ")"
            );
        }
    }

    // Make sure `sprites` is the same size as `tiles`
    if (sprites.size() != tiles.size())
    {
        throw std::invalid_argument(
            "`drops` does not have the same number of rows as `tiles`"
        );
    }
    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i].size() != sprites[i].size())
        {
            throw std::invalid_argument(
                std::string("`sprites` does not have the same number of columns as `tiles` (row ") +
                std::to_string(curr_row) + ")"
            );
        }
    }
    // Make sure exactly one PlayerSprite has been defined
    bool player_found = false;
    for (auto row : sprites)
    {
        for (auto sprite : row)
        {
            if (sprite && sprite->getSpriteType() == SpriteType::PLAYER)
            {
                if (player_found)
                {
                    throw std::invalid_argument(
                        "More than one Player location defined"
                    );
                }
                else
                {
                    player_found = true;
                }
            }
        }
    }
    if (!player_found)
    {
        throw std::invalid_argument(
            "No Player location defined"
        );
    }
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

ObjectType Map::resolveObjectType(int objectId)
{
    switch (objectId)
    {
        case 1:
        {
            return ObjectType::ROCK;
        }
        default:
        {
            throw std::invalid_argument(
                std::string("Unsupported object ID ") + 
                std::to_string(objectId)
            );
        }
    }
}

ItemType Map::resolveItemType(int itemId)
{
    switch (itemId)
    {
        case 1:
        {
            return ItemType::PICKAXE;
        }
        case 2:
        {
            return ItemType::GRAVEL;
        }
        default:
        {
            throw std::invalid_argument(
                std::string("Unsupported ItemID ") + 
                std::to_string(itemId)
            );
        }
    }
}

SpriteType Map::resolveSpriteType(int spriteId)
{
    switch (spriteId)
    {
        case 1:
        {
            return SpriteType::PLAYER;
        }
        case 2:
        {
            return SpriteType::FRIENDLY;
        }
        default:
        {
            throw std::invalid_argument(
                std::string("Unsupported SpriteID ") + 
                std::to_string(spriteId)
            );
        }
    }
}