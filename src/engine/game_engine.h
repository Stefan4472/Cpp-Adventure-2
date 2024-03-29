#ifndef _GAME_ENGINE_H
#define _GAME_ENGINE_H

#include <SDL2/SDL.h>
#include <boost/filesystem.hpp>
#include <memory>
#include <queue>
#include <list>
#include <random>
#include <iostream>
#include "input_event.h"
#include "texture_cache.h"
#include "map.h"
#include "game_context.h"
#include "engine_interface.h"
#include "update_context.h"
#include "game_renderer.h"


class GameEngine : public EngineInterface
{
public:
    // TODO: GAMEENGINE SHOULDN'T DEAL WITH THE RENDERER AT ALL...
    // OR ANYTHING RELATED TO SDL
    GameEngine(
        boost::filesystem::path rootPath,
        SDL_Renderer* renderer,
        int gameWidth,
        int gameHeight
    );
    
    std::shared_ptr<GameContext> getGameContextForTesting();
    std::shared_ptr<Map> getMapForTesting();

    // Handle player input
    void giveInput(EventId eventId);
    
    /* `EngineInterface` methods */
    bool isTileWithinMap(
        int tileX, 
        int tileY
    );
    bool isTileWalkable(
        int tileX,
        int tileY
    );
    std::pair<int, int> resolveTile(
        double worldX, 
        double worldY
    );
    bool requestMoveToTile(
        Sprite* sprite,
        int currTileX, 
        int currTileY,
        int newTileX, 
        int newTileY
    );
    std::pair<int, int> getPlayerTile();
    int genRandInt1To100();

    // Update game state
    void update();
    // Draw game to provided Renderer
    void draw(SDL_Renderer* renderer);
    

private:
    // TODO: PROBABLY NEED A THREAD-SAFE QUEUE
    std::queue<EventId> inputQueue;

    std::shared_ptr<TextureCache> textureCache;
    std::shared_ptr<GameRenderer> gameRenderer;
    std::shared_ptr<Map> map;
    std::shared_ptr<GameContext> gameContext;

    uint32_t prevUpdateMs;

    // Used for random number generation
    std::default_random_engine randEngine;
    std::uniform_int_distribution<int> randDistribution;

    void handleInput(
        EventId inputId, 
        UpdateContext* updateContext
    );

    void executeInteraction(
        InteractRequest& interactRequest,
        UpdateContext& updateContext
    );
};

#endif