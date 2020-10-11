#ifndef _UPDATE_CONTEXT_H
#define _UPDATE_CONTEXT_H
#include <stdint.h>

struct UpdateContext
{
    uint32_t gameRuntimeMs;
    uint32_t msSincePrevUpdate;
};

#endif