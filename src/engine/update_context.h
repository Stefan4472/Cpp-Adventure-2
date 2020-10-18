#ifndef _UPDATE_CONTEXT_H
#define _UPDATE_CONTEXT_H
#include <stdint.h>
#include <list>
#include "engine_requests.h"
#include "game_context.h"

// TODO: REMOVE
#include <iostream>

class UpdateContext
{
public:
    UpdateContext(
        GameContext* gameContext,
        uint32_t gameRuntimeMs,
        uint32_t msSincePrevUpdate,
        std::list<InteractRequest>& interactions,
        std::list<CreateObjectRequest>& createObjectRequests,
        std::list<DestroyObjectRequest>& destroyObjectRequests,
        std::list<ReplaceTileRequest>& replaceTileRequests,
        std::list<CreateDropRequest>& createDropRequests
    );

    // TODO: MAKE PRIVATE
    uint32_t gameRuntimeMs;
    uint32_t msSincePrevUpdate;

    void requestInteract(
        Sprite* actor, 
        Item* withItem, 
        int tileX, 
        int tileY
    );

    void requestCreateObject(
        ObjectType objectType,
        int tileX,
        int tileY
    );

    void requestDestroyObject(
        int tileX,
        int tileY
    );

    void requestReplaceTile(
        TileType tileType,
        int tileX,
        int tileY
    );

    void requestCreateDrop(
        ItemType itemType,
        int quantity,
        int tileX, 
        int tileY
    );

    // `Move-Tile` requests are different, because they
    // must return instantly. They are handled synchronously
    // by the Map.
    bool requestMoveToTile(
        Sprite* sprite,
        int currTileX, 
        int currTileY,
        int newTileX, 
        int newTileY
    );

private:
    GameContext* gameContext;
    std::list<InteractRequest>* interactions;
    std::list<CreateObjectRequest>* createObjectRequests;
    std::list<DestroyObjectRequest>* destroyObjectRequests;
    std::list<ReplaceTileRequest>* replaceTileRequests;
    std::list<CreateDropRequest>* createDropRequests;
};

#endif