#include "game_engine.h"

GameEngine::GameEngine()
{

}

void GameEngine::handleUpPressed()
{
    inputQueue.push(EventId::PRESS_UP);
}

void GameEngine::handleDownPressed()
{
    inputQueue.push(EventId::PRESS_DOWN);
}

void GameEngine::handleLeftPressed()
{
    inputQueue.push(EventId::PRESS_LEFT);
}

void GameEngine::handleRightPressed()
{
    inputQueue.push(EventId::PRESS_RIGHT);
}

void GameEngine::update()
{
    while (!inputQueue.empty())
    {
        EventId next_input = inputQueue.front();
        std::cout << int(next_input) << std::endl;
        inputQueue.pop();
        std::cout << "Now have " + std::to_string(inputQueue.size()) + " elements" << std::endl;
    }
}