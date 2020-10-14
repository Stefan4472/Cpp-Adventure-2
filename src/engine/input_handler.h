#ifndef _INPUT_HANDLER_H
#define _INPUT_HANDLER_H

#include <list>
#include <stdexcept>
#include "input_event.h"
#include "direction.h"


// Manages input given to the Player Sprite
class InputHandler
{
public:
    void giveInput(EventId eventId);
    Direction getNextWalkCommand();

private:
    // List of movement commands, in increasing priority.
    // The last element is the one that is currently being applied.
    // If list is empty, then there is no current movement input.
    std::list<EventId> moveCommands;
};

#endif