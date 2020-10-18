#include "game_engine.h"

GameEngine::GameEngine(
        boost::filesystem::path rootPath,
        SDL_Renderer* renderer,
        int gameWidth,
        int gameHeight
) : randDistribution(0, 100)
{
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

    prevUpdateMs = 0;
}

std::shared_ptr<GameContext> GameEngine::getGameContextForTesting()
{
    return gameContext;
}

std::shared_ptr<Map> GameEngine::getMapForTesting()
{
    return map;
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

bool GameEngine::requestMoveToTile(
        Sprite* sprite,
        int currTileX, 
        int currTileY,
        int newTileX, 
        int newTileY
) {
    return map->requestMoveToTile(
        sprite,
        currTileX,
        currTileY,
        newTileX,
        newTileY
    );
}

std::pair<int, int> GameEngine::getPlayerTile()
{
    return map->getPlayerActor()->getTileCoords();
}

int GameEngine::genRandInt1To100()
{
    return randDistribution(randEngine);
}

void GameEngine::update()
{
    uint32_t curr_game_time = SDL_GetTicks();
    if (!prevUpdateMs)
    {
        prevUpdateMs = SDL_GetTicks();
    }
    uint32_t ms_since_prev = curr_game_time - prevUpdateMs;
 
    // TODO: RENAME: E.G., `INTERACT_REQUESTS`, `CREATE_OBJECT_REQUESTS`
    std::list<InteractRequest> req_interactions;
    std::list<CreateObjectRequest> req_created_objects;
    std::list<DestroyObjectRequest> req_destroyed_objects;
    std::list<ReplaceTileRequest> req_replaced_tiles;
    std::list<CreateDropRequest> req_created_drops;
 
    // Create UpdateContext
    UpdateContext update_context = {
        gameContext.get(),
        curr_game_time,
        ms_since_prev,
        req_interactions,
        req_created_objects,
        req_destroyed_objects,
        req_replaced_tiles,
        req_created_drops
    };

    // Handle any input queued since last update
    while (!inputQueue.empty())
    {
        EventId next_input = inputQueue.front();
        handleInput(next_input, &update_context);
        inputQueue.pop();
    }

    map->update(update_context);

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
        // TODO: HOW TO REPORT TO THE ITEM/OWNER THAT IT WAS SUCCESSFULLY
        // PLACED, THUS CONSUMING IT?
        if (map->canCreateObjectAtTile(create_request.tileX, create_request.tileY))
        {
            map->createObjectAtTile(
                create_request.objectType,
                create_request.tileX,
                create_request.tileY
            );
        }
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
    for (CreateDropRequest drop_request : req_created_drops)
    {
        auto dropped_item = ItemFactory::createItem(
            gameContext.get(),
            drop_request.itemType
        );
        map->createDropAtTile(
            dropped_item,
            drop_request.tileX,
            drop_request.tileY
        );
    }
    prevUpdateMs = curr_game_time;
}

void GameEngine::handleInput(EventId inputId, UpdateContext* updateContext)
{
    // Pass input to the Player
    map->getPlayerActor()->giveInput(
        inputId, 
        updateContext
    );
}

void GameEngine::executeInteraction(
        InteractRequest& iRequest,
        UpdateContext& updateContext
) {
    /*
    TODO: DISTINGUISH BETWEEN 'INTERACT' AND 'ACTION'---ACTUALLY TWO DIFFERENT THINGS
    The Interaction is handled in the following priority:
    1. Check if the request involves an Item (if not, try to pick up a drop)
    1. Check if the request places a MapObject
    2. Check if the request places a Tile
    3. Check if the request has hit a Sprite
    4. Check if the request has hit a MapObject
    5. Check if the request has hit a Tile

    Function exits as soon as one of these conditions has been
    met and applied.
    */

    // Ignore out-of-bounds requests
    if (!map->isTileWithinMap(iRequest.tileX, iRequest.tileY))
    {
        return;
    }

    if (!iRequest.item)
    {
        std::cout << "No in-hand item: will try to pick up a drop" << std::endl;
        std::shared_ptr<Drop> drop_at_tile = map->getDropAtTile(
            iRequest.tileX,
            iRequest.tileY
        );
        // There is a drop to pick up--give its Item to the Sprite,
        // and remove it from the map
        if (drop_at_tile)
        {
            std::cout << "Got drop: " << drop_at_tile << " with item " << 
                drop_at_tile->getItem() << std::endl;
            // Attempt to give to Sprite
            auto sprite_actor = map->lookupSpriteActor(iRequest.sprite);
            if (sprite_actor->giveItem(drop_at_tile->getItem()))
            {
                // Sprite took the item. Now remove the drop
                map->removeDropAtTile(
                    iRequest.tileX,
                    iRequest.tileY
                );
            }
        }
        return;
    }
    // Check if the interaction creates+places a MapObject
    if (iRequest.item->isPlaceableAsObject())
    {
        updateContext.requestCreateObject(
            iRequest.item->getObjectPlaced(),
            iRequest.tileX,
            iRequest.tileY
        );
        return;
    }

    // Check if the interaction places a Tile
    if (iRequest.item->isPlaceableAsTile())
    {
        updateContext.requestReplaceTile(
            iRequest.item->getTilePlaced(),
            iRequest.tileX,
            iRequest.tileY
        );
        return;
    }

    // Check if the interaction has hit a Sprite (TODO)
    // std::shared_ptr<Sprite> interacted_sprite =
    //     map->getSpriteAtTile(iRequest.tileX, iRequest.tileY);
    // if (interacted_sprite)
    // {
    //     //.....
    // }

    // Check if the interaction has hit a MapObject
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
        return;
    }

    // Check if the interaction has hit a Tile
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
    std::tie(player_x, player_y) = 
        map->getPlayerActor()->getWorldCoords();

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

    map->drawSprites(
        gameRenderer.get(),
        visible_bounds
    );
}