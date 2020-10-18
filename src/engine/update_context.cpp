#include "update_context.h"

UpdateContext::UpdateContext(
        uint32_t gameRuntimeMs,
        uint32_t msSincePrevUpdate,
        std::list<InteractRequest>& interactions,
        std::list<CreateObjectRequest>& createObjectRequests,
        std::list<DestroyObjectRequest>& destroyObjectRequests,
        std::list<ReplaceTileRequest>& replaceTileRequests,
        std::list<CreateDropRequest>& createDropRequests
) {
    this->gameRuntimeMs = gameRuntimeMs;
    this->msSincePrevUpdate = msSincePrevUpdate;
    this->interactions = &interactions;
    this->createObjectRequests = &createObjectRequests;
    this->destroyObjectRequests = &destroyObjectRequests;
    this->replaceTileRequests = &replaceTileRequests;
    this->createDropRequests = &createDropRequests;
}

void UpdateContext::requestInteract(
        Sprite* actor, 
        Item* withItem, 
        int tileX, 
        int tileY
) {
    interactions->push_back(InteractRequest{
        actor,
        withItem,
        tileX,
        tileY
    });
}

void UpdateContext::requestCreateObject(
        ObjectType objectType,
        int tileX,
        int tileY
) {
    createObjectRequests->push_back(CreateObjectRequest{
        objectType,
        tileX,
        tileY
    });
}

void UpdateContext::requestDestroyObject(
        int tileX,
        int tileY
) {
    destroyObjectRequests->push_back(DestroyObjectRequest{
        tileX,
        tileY
    });
}

void UpdateContext::requestReplaceTile(
        TileType tileType,
        int tileX,
        int tileY
) {
    replaceTileRequests->push_back(ReplaceTileRequest{
        tileType,
        tileX,
        tileY
    });
}

void UpdateContext::requestCreateDrop(
        ItemType itemType,
        int quantity,
        int tileX, 
        int tileY
) {
    createDropRequests->push_back(CreateDropRequest{
        itemType,
        quantity,
        tileX,
        tileY
    });
}

bool UpdateContext::requestMoveToTile(
        Sprite* sprite,
        int currTileX, 
        int currTileY,
        int newTileX, 
        int newTileY
) {
    std::cout << "Move tile request for sprite " << sprite << " to " <<
        newTileX << ", " << newTileY << std::endl;
}