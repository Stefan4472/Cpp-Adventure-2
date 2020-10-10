#include "game_engine.h"

GameEngine::GameEngine(
        boost::filesystem::path rootPath,
        int gameWidth,
        int gameHeight,
        SDL_Renderer* renderer
)
{
    std::cout << "Init GameEngine with width,height " << gameWidth << ", " << gameHeight << std::endl;
    auto graphics_path = rootPath / "graphics";
    auto map_path = rootPath / "map.txt";

    textureCache = std::make_shared<TextureCache>(
        graphics_path,
        renderer
    );
    
    map = std::make_shared<Map>(
        Map::fromFile(map_path)
    );

    gameContext = std::make_shared<GameContext>(
        gameWidth,
        gameHeight,
        TILE_SIZE_PX,
        textureCache,
        map
    );

    player = std::make_shared<PlayerSprite>(
        gameContext, 
        SpriteType::PLAYER, 
        320, 
        256
    );
}

void GameEngine::giveInput(EventId eventId)
{
    inputQueue.push(eventId);
}

void GameEngine::update()
{
    while (!inputQueue.empty())
    {
        EventId next_input = inputQueue.front();
        handleInput(next_input);
        inputQueue.pop();
    }

    if (!prevUpdateMs)
    {
        prevUpdateMs = SDL_GetTicks();
    }

    uint32_t curr_game_time = SDL_GetTicks();
    uint32_t ms_since_prev = curr_game_time - prevUpdateMs;

    UpdateContext update_context = {
        curr_game_time,
        ms_since_prev
    };

    player->update(&update_context);

    prevUpdateMs = curr_game_time;
}

void GameEngine::handleInput(EventId inputId)
{
    // Pass input to the Player
    player->giveInput(inputId);
}

void GameEngine::draw(SDL_Renderer* renderer)
{
    // Draw tiles
    SDL_Rect dest_rect;
    for (int i = 0; i < map->numRows; i++)
    {
        for (int j = 0; j < map->numCols; j++)
        {
            dest_rect.x = j * TILE_SIZE_PX;
            dest_rect.y = i * TILE_SIZE_PX;
            dest_rect.w = TILE_SIZE_PX;
            dest_rect.h = TILE_SIZE_PX;
            // Look up the TextureId for this tile
            TextureId tile_texture = getTileTextureId(map->mapTiles[i][j]);

            SDL_RenderCopy(
                renderer,
                textureCache->getTexture(tile_texture), 
                NULL,
                &dest_rect
            );
        }
    }
    
    // Draw player
    player->draw(renderer);
}