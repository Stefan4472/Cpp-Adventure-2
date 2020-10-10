#include "game_engine.h"

GameEngine::GameEngine(
        boost::filesystem::path rootPath,
        SDL_Renderer* renderer,
        int gameWidth,
        int gameHeight
) {
    std::cout << "Init GameEngine with width,height " << gameWidth << ", " << gameHeight << std::endl;
    auto graphics_path = rootPath / "graphics";
    auto map_path = rootPath / "map.txt";

    textureCache = std::make_shared<TextureCache>(
        graphics_path,
        renderer
    );
    
    gameRenderer = std::make_shared<GameRenderer>(
        renderer,
        textureCache,
        gameWidth,
        gameHeight
    );

    map = std::make_shared<Map>(
        Map::fromFile(map_path)
    );

    gameContext = std::make_shared<GameContext>(
        gameWidth,
        gameHeight,
        TextureCache::TILE_SIZE_PX,
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
    int world_width, world_height;
    std::tie(world_width, world_height) = 
        map->getSizePx();

    // Center viewable area on player
    double top_left_wx = 
        player->worldX - gameContext->screenWidth / 2;
    double top_left_wy = 
        player->worldY - gameContext->screenHeight / 2;
    
    // Set x- and y- so that we don't go past the edge of the world
    if (top_left_wx < 0.0)
    {
        top_left_wx = 0.0;
    }
    else if (top_left_wx + gameContext->screenWidth > world_width)
    {
        top_left_wx = world_width - gameContext->screenWidth;
    }
    if (top_left_wy < 0.0)
    {
        top_left_wy = 0.0;
    }
    else if (top_left_wy + gameContext->screenHeight > world_height)
    {
        top_left_wy = world_height - gameContext->screenHeight;
    }

    SDL_Rect visible_bounds = {
        static_cast<int>(top_left_wx),
        static_cast<int>(top_left_wy),
        gameContext->screenWidth,
        gameContext->screenHeight    
    };

    gameRenderer->setTopLeftCoord(
        top_left_wx, 
        top_left_wy
    );

    map->drawTiles(
        gameRenderer.get(),
        visible_bounds
    );
    
    // Draw player
    player->draw(gameRenderer.get());
}