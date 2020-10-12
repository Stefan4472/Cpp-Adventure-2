#include "update_context.h"

UpdateContext::UpdateContext(
        uint32_t gameRuntimeMs,
        uint32_t msSincePrevUpdate,
        std::list<InteractRequest>& interactions,
        std::list<CreateObjectRequest>& createObjectRequests,
        std::list<DestroyObjectRequest>& destroyObjectRequests,
        std::list<ReplaceTileRequest>& replaceTileRequests
) {
    this->gameRuntimeMs = gameRuntimeMs;
    this->msSincePrevUpdate = msSincePrevUpdate;
    this->interactions = &interactions;
    this->createObjectRequests = &createObjectRequests;
    this->destroyObjectRequests = &destroyObjectRequests;
    this->replaceTileRequests = &replaceTileRequests;
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