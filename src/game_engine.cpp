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
    SDL_Rect visible_bounds = {
        0,
        0,
        gameContext->screenWidth,
        gameContext->screenHeight    
    };

    map->draw(
        gameRenderer.get(),
        visible_bounds
    );
    
    // Draw player
    player->draw(gameRenderer.get());
}