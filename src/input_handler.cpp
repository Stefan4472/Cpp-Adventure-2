#include "input_handler.h"

void InputHandler::giveInput(EventId eventId)
{
    switch (eventId)
    {
        // Push "down" inputs onto the list
        case EventId::PRESS_UP:
        case EventId::PRESS_DOWN:
        case EventId::PRESS_LEFT:
        case EventId::PRESS_RIGHT:
        {
            moveCommands.push_back(eventId);
            break;
        }
        // For "up" inputs, search and remove the corresponding
        // "down" input from the list
        case EventId::UNPRESS_UP:
        {
            moveCommands.remove(EventId::PRESS_UP);
            break;
        }
        case EventId::UNPRESS_DOWN:
        {
            moveCommands.remove(EventId::PRESS_DOWN);
            break;
        }
        case EventId::UNPRESS_LEFT:
        {
            moveCommands.remove(EventId::PRESS_LEFT);
            break;
        }
        case EventId::UNPRESS_RIGHT:
        {
            moveCommands.remove(EventId::PRESS_RIGHT);
            break;
        }
        default:
        {
            ;
        }

    }
}

WalkDirection InputHandler::getNextWalkCommand()
{
    if (moveCommands.empty())
    {
        return WalkDirection::NONE;
    }
    else
    {
        switch (moveCommands.back())
        {
            case EventId::PRESS_UP:
            {
                return WalkDirection::UP;
            }
            case EventId::PRESS_DOWN:
            {
                return WalkDirection::DOWN;
            }
            case EventId::PRESS_LEFT:
            {
                return WalkDirection::LEFT;
            }
            case EventId::PRESS_RIGHT:
            {
                return WalkDirection::RIGHT;
            }
            default:
            {
                throw std::invalid_argument(
                    "Unsupported/Illegal EventId on `moveCommands` list (programmer error)"
                );
            }
        }
    }
}