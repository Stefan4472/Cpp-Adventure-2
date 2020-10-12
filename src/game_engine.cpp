#include "game_engine.h"

GameEngine::GameEngine(
        boost::filesystem::path rootPath,
        SDL_Renderer* renderer,
        int gameWidth,
        int gameHeight
) {
    std::cout << "Init GameEngine at " << rootPath << " with width,height " << gameWidth << ", " << gameHeight << std::endl;
    auto graphics_path = rootPath / "graphics";
    auto map_path = rootPath / "map";

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

    gameContext = std::make_shared<GameContext>(
        gameWidth,
        gameHeight,
        TextureCache::TILE_SIZE_PX,
        textureCache,
        this
    );

    // TODO/NOTE: WARNING: THE CONTEXT IS NOT FULLY FINISHED AT THIS POINT
    // (BECAUSE THE MAP HAS NOT BEEN INITIALIZED). THIS IS A CHICKEN-AND-EGG
    // PROBLEM, BASICALLY. LEAVING IT FOR NOW.
    map = std::make_shared<Map>(Map::loadMap(
        gameContext.get(), 
        map_path
    ));


    SDL_Rect player_start_tile = {
        320, 
        256, 
        TextureCache::TILE_SIZE_PX, 
        TextureCache::TILE_SIZE_PX
    };

    player = std::make_shared<PlayerSprite>(
        gameContext, 
        player_start_tile
    );
    player->inHandItem = std::make_shared<PickaxeItem>();
}

void GameEngine::giveInput(EventId eventId)
{
    inputQueue.push(eventId);
}

bool GameEngine::isTileWithinMap(
    int tileX, 
    int tileY
) {
    if (map)
    {
        return map->isTileWithinMap(tileX, tileY);
    }
    else
    {
        std::cout << "WARN: GameEngine method called before Map finished initialized" << std::endl;
    }
    
}

bool GameEngine::isTileWalkable(
    int tileX,
    int tileY
) {
    if (map)
    {
        return map->isTileWalkable(tileX, tileY);
    }
    else
    {
        std::cout << "WARN: GameEngine method called before Map finished initialized" << std::endl;
    }
}

std::pair<int, int> GameEngine::resolveTile(
    double worldX, 
    double worldY
) {
    if (map)
    {
        return map->resolveTile(worldX, worldY);
    }
    else
    {
        std::cout << "WARN: GameEngine method called before Map finished initialized" << std::endl;
    }
}

void GameEngine::update()
{
    uint32_t curr_game_time = SDL_GetTicks();
    uint32_t ms_since_prev = curr_game_time - prevUpdateMs;
    std::list<InteractRequest> req_interactions;
    std::list<CreateObjectRequest> req_created_objects;
    std::list<DestroyObjectRequest> req_destroyed_objects;
    std::list<ReplaceTileRequest> req_replaced_tiles;

    UpdateContext update_context = {
        curr_game_time,
        ms_since_prev,
        req_interactions,
        req_created_objects,
        req_destroyed_objects,
        req_replaced_tiles
    };

    while (!inputQueue.empty())
    {
        EventId next_input = inputQueue.front();
        handleInput(next_input, &update_context);
        inputQueue.pop();
    }

    if (!prevUpdateMs)
    {
        prevUpdateMs = SDL_GetTicks();
    }

    // TODO: ACTUALLY PASS BY REFERENCE
    player->update(&update_context);

    // Execute all requested interactions
    for (InteractRequest irequest : req_interactions)
    {
        std::cout << irequest.sprite << ": " << irequest.item << 
            " at " << irequest.tileX << ", " << irequest.tileY << std::endl;
        executeInteraction(irequest, update_context);
    }

    /* Finally, fulfill all requests */
    for (CreateObjectRequest create_request : req_created_objects)
    {
        map->createObjectAtTile(
            create_request.objectType,
            create_request.tileX,
            create_request.tileY
        );
    }
    for (DestroyObjectRequest destroy_request : req_destroyed_objects)
    {
        map->removeObjectAtTile(
            destroy_request.tileX,
            destroy_request.tileY
        );
    }
    for (ReplaceTileRequest replace_request : req_replaced_tiles)
    {
        map->replaceTile(
            replace_request.tileType,
            replace_request.tileX,
            replace_request.tileY
        );
    }
    prevUpdateMs = curr_game_time;
}

void GameEngine::handleInput(EventId inputId, UpdateContext* updateContext)
{
    // Pass input to the Player
    player->giveInput(inputId, updateContext);
}

void GameEngine::executeInteraction(
        InteractRequest& iRequest,
        UpdateContext& updateContext
) {
    // Ignore out-of-bounds requests
    if (!map->isTileWithinMap(iRequest.tileX, iRequest.tileY))
    {
        return;
    }
    // Check first if Sprite is at tile, then if object, then tile itself

    // std::shared_ptr<Sprite> interacted_sprite =
    //     map->getSpriteAtTile(iRequest.tileX, iRequest.tileY);
    // if (interacted_sprite)
    // {
    //     //.....
    // }

    std::shared_ptr<MapObject> interacted_object =
        map->getObjectAtTile(iRequest.tileX, iRequest.tileY);
    if (interacted_object)
    {
        //.....
        std::cout << "Interacting with object " << interacted_object << std::endl;
        // Notify target
        interacted_object->respondToInteract(
            updateContext,
            iRequest.sprite,
            iRequest.item
        );
        // Notify Item
        iRequest.item->onFinishedInteract(
            interacted_object->getObjectType()
        );
        // if (interacted_object->getRemoveFromGame())
        // {
        //     map->removeObjectAtTile(iRequest.tileX, iRequest.tileY);
        // }
        return;
    }

    std::shared_ptr<Tile> interacted_tile =
        map->getTile(iRequest.tileX, iRequest.tileY);
    if (interacted_tile)
    {
        //.....
        std::cout << "Interacting with tile " << interacted_tile << std::endl;
        interacted_tile->respondToInteract(
            updateContext,
            iRequest.sprite,
            iRequest.item
        );
        iRequest.item->onFinishedInteract(
            interacted_tile->getTileType()
        );
        return;
    }

}

void GameEngine::draw(SDL_Renderer* renderer)
{
    int world_width, world_height;
    std::tie(world_width, world_height) = map->getSizePx();

    double player_x, player_y;
    std::tie(player_x, player_y) = player->getWorldCoords();

    // Center viewable area on player
    double top_left_wx = 
        player_x - gameContext->screenWidth / 2;
    double top_left_wy = 
        player_y - gameContext->screenHeight / 2;
    
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
    
    map->drawObjects(
        gameRenderer.get(),
        visible_bounds    
    );

    // Draw player
    player->draw(gameRenderer.get());
}