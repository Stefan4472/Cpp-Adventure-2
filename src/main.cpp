#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
// Following two imports used to sleep between loops
#include <chrono>
#include <thread>
#include "game_engine.h"


// Path to project directory root
const boost::filesystem::path ROOT_PATH("/home/stefan/Cpp-Adventure-2");

// Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 512;

// The window we'll be rendering to
SDL_Window* gWindow = NULL;
// Renderer used by the window
SDL_Renderer* gRenderer = NULL;

// Starts up SDL and creates window
bool init();
// Frees media and shuts down SDL
void close();


int main(int argc, char* args[])
{
    if (!init())
    {
        std::cout << "Failed to initialize" << std::endl;;
        exit(1);
    }

    // Create GameEngine
    GameEngine gameEngine(
        ROOT_PATH,
        gRenderer,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    );

    bool quit = false;
    SDL_Event next_event;
    // Main loop
    while (!quit)
    {
        // Handle events on queue.
        // This is where we translate SDL_Events into input events
        // that our engine understands.
        while (SDL_PollEvent(&next_event) != 0)
        {
            // User requests quit
            if (next_event.type == SDL_QUIT)
            {
                quit = true;
            }
            // User presses a key
            else if (next_event.type == SDL_KEYDOWN && !next_event.key.repeat)
            {
                switch(next_event.key.keysym.sym)
                {
                    case SDLK_UP:
                    {
                        gameEngine.giveInput(EventId::PRESS_UP);
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        gameEngine.giveInput(EventId::PRESS_DOWN);
                        break;
                    }
                    case SDLK_LEFT:
                    {
                        gameEngine.giveInput(EventId::PRESS_LEFT);
                        break;
                    }
                    case SDLK_RIGHT:
                    {
                        gameEngine.giveInput(EventId::PRESS_RIGHT);
                        break;
                    }
                    case SDLK_SPACE:
                    {
                        gameEngine.giveInput(EventId::PRESS_ACTION);
                        break;
                    }
                    case SDLK_TAB:
                    {
                        gameEngine.giveInput(EventId::ROTATE_INVENTORY);
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
            // User releases a key
            else if (next_event.type == SDL_KEYUP)
            {
                switch(next_event.key.keysym.sym)
                {
                    case SDLK_UP:
                    {
                        gameEngine.giveInput(EventId::UNPRESS_UP);
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        gameEngine.giveInput(EventId::UNPRESS_DOWN);
                        break;
                    }
                    case SDLK_LEFT:
                    {
                        gameEngine.giveInput(EventId::UNPRESS_LEFT);
                        break;
                    }
                    case SDLK_RIGHT:
                    {
                        gameEngine.giveInput(EventId::UNPRESS_RIGHT);
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }
    
        // Update game
        gameEngine.update();
        // Clear screen
        SDL_RenderClear(gRenderer);
        // Draw game graphics
        gameEngine.draw(gRenderer);
        // Update window
        SDL_RenderPresent(gRenderer);

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }

	close();
}

bool init()
{
    // Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << std::string(SDL_GetError()) << std::endl;
        return false;
	}

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << std::string(IMG_GetError()) << std::endl;
        return false;
    }
    
    // Create window
    gWindow = SDL_CreateWindow(
        "Stefan's C++ Game", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        SDL_WINDOW_SHOWN
    );

    if (gWindow == NULL)
    {
        std::cout << "Window could not be created! SDL_Error: " << std::string(SDL_GetError()) << std::endl;
        return false;
    }

    //Create renderer for window
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL)
    {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
     
    // Initialize renderer color
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return true;
}

void close()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    SDL_Quit();
    IMG_Quit();
}