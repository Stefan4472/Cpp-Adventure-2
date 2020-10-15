#ifndef _GAME_ENGINE_H
#define _GAME_ENGINE_H

#include <SDL2/SDL.h>
#include <boost/filesystem.hpp>
#include <memory>
#include <queue>
#include <list>
#include <iostream>
#include "input_event.h"
#include "texture_cache.h"
#include "map.h"
#include "game_context.h"
#include "engine_interface.h"
#include "update_context.h"
#include "game_renderer.h"

// TODO: REMOVE
#include "player_actor.h"
#include "npc_actor.h"

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

    // TODO: REMOVE
    std::shared_ptr<PlayerActor> playerActor;
    std::shared_ptr<Actor> npcActor;
    
    uint32_t prevUpdateMs;

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