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

// Starts up SDL and creates window
bool init();
// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window* gWindow = NULL;
// The surface contained by the window
SDL_Surface* gScreenSurface = NULL;


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
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    );

    bool quit = false;
    SDL_Event next_event;
    // Main loop
    while (!quit)
    {
        // Handle events on queue
        while (SDL_PollEvent(&next_event) != 0)
        {
            // User requests quit
            if (next_event.type == SDL_QUIT)
            {
                quit = true;
            }
            // User presses a key
            else if (next_event.type == SDL_KEYDOWN)
            {
                switch(next_event.key.keysym.sym)
                {
                    case SDLK_UP:
                    {
                        std::cout << "Pressed the <UP> key" << std::endl;
                        gameEngine.inputUpPressed();
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        std::cout << "Pressed the <DOWN> key" << std::endl;
                        gameEngine.inputDownPressed();
                        break;
                    }
                    case SDLK_LEFT:
                    {
                        std::cout << "Pressed the <LEFT> key" << std::endl;
                        gameEngine.inputLeftPressed();
                        break;
                    }
                    case SDLK_RIGHT:
                    {
                        std::cout << "Pressed the <RIGHT> key" << std::endl;
                        gameEngine.inputRightPressed();
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }
    
        gameEngine.update();

        // Fill the surface white
        SDL_FillRect(
            gScreenSurface, 
            NULL, 
            SDL_MapRGB(
                gScreenSurface->format, 
                0xFF, 
                0xFF, 
                0xFF
            )
        );

        // Draw game graphics
        gameEngine.draw(gScreenSurface);

        // Update surface
        SDL_UpdateWindowSurface(gWindow);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
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

    // Get window surface
    gScreenSurface = SDL_GetWindowSurface(gWindow);
    return true;
}

void close()
{
    // Deallocate surface
    SDL_FreeSurface(gScreenSurface);
    gScreenSurface = NULL;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}