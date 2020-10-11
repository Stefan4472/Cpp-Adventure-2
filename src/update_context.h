#ifndef _UPDATE_CONTEXT_H
#define _UPDATE_CONTEXT_H
#include <stdint.h>
#include <list>
#include "interact_request.h"


class UpdateContext
{
public:
    UpdateContext(
        uint32_t gameRuntimeMs,
        uint32_t msSincePrevUpdate,
        std::list<InteractRequest>* interactions
    );

    void requestInteract(
        Sprite* actor, 
        Item* withItem, 
        int tileX, 
        int tileY
    );

    uint32_t gameRuntimeMs;
    uint32_t msSincePrevUpdate;

private:
    std::list<InteractRequest>* interactions;
};

#endif