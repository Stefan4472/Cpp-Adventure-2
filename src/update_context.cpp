#include "update_context.h"

UpdateContext::UpdateContext(
        uint32_t gameRuntimeMs,
        uint32_t msSincePrevUpdate,
        std::list<InteractRequest>* interactions
) {
    this->gameRuntimeMs = gameRuntimeMs;
    this->msSincePrevUpdate = msSincePrevUpdate;
    this->interactions = interactions;
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