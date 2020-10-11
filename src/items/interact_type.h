#ifndef _INTERACT_TYPE_H
#define _INTERACT_TYPE_H

// The possible "classes" with which an item can interact.
// TODO: OR, PERHAPS, WE ALWAYS FIRST CHECK AGAINST SPRITE, THEN AGAINST OBJECT, THEN AGAINST TILE?
enum class InteractType
{
    OBJECT_ONLY,
    TILE_ONLY,
    SPRITE_ONLY
};

#endif