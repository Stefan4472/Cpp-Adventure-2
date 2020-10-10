#ifndef _GAME_ENGINE_H
#define _GAME_ENGINE_H

#include <SDL2/SDL.h>
#include <boost/filesystem.hpp>
#include <memory>
#include <queue>
#include <iostream>
#include "input_event.h"

#include "texture_id.h"
#include "texture_cache.h"
#include "map.h"
#include "tile_type.h"
#include "game_context.h"
#include "sprite.h"
#include "player_sprite.h"
#include "update_context.h"


class GameEngine
{
public:
    // TODO: GAMEENGINE SHOULDN'T DEAL WITH THE RENDERER AT ALL
    GameEngine(
            boost::filesystem::path rootPath,
            int gameWidth,
            int gameHeight,
            SDL_Renderer* renderer
    );

    // TODO: INCREASE TILE WIDTH TO 64X64? (BETTER RESOLUTION)
    const int TILE_SIZE_PX = 32;
    
    // Handle player input
    void giveInput(EventId eventId);
    // Update game state
    void update();
    // Draw game to provided Renderer
    void draw(SDL_Renderer* renderer);
    

private:
    // TODO: PROBABLY NEED A THREAD-SAFE QUEUE
    std::queue<EventId> inputQueue;

    std::shared_ptr<TextureCache> textureCache;
    std::shared_ptr<Map> map;
    std::shared_ptr<GameContext> gameContext;
    std::shared_ptr<PlayerSprite> player;

    uint32_t prevUpdateMs;

    void handleInput(EventId inputId);
};

#endif