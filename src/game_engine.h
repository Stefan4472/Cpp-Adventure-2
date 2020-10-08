#ifndef _GAME_ENGINE_H
#define _GAME_ENGINE_H

#include <queue>
#include "input_event.h"
#include <iostream>

class GameEngine
{
public:
    GameEngine();
    
    /* Input handlers */
    void handleUpPressed();
    void handleDownPressed();
    void handleLeftPressed();
    void handleRightPressed();

    void update();

private:
    // TODO: PROBABLY NEED A THREAD-SAFE QUEUE
    std::queue<EventId> inputQueue;
};

#endif