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
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        gRenderer
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
                        gameEngine.inputUpPressed();
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        gameEngine.inputDownPressed();
                        break;
                    }
                    case SDLK_LEFT:
                    {
                        gameEngine.inputLeftPressed();
                        break;
                    }
                    case SDLK_RIGHT:
                    {
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
    
        // Update game
        gameEngine.update();
        // Clear screen
        SDL_RenderClear(gRenderer);
        // Draw game graphics
        gameEngine.draw(gRenderer);

        // SDL_Surface* surface = IMG_Load("../graphics/sprite-front.png");
        // if (surface == NULL)
        // {
        //     throw std::runtime_error(
        //         "Couldn't load image: SDL_Error " + std::string(SDL_GetError())
        //     );
        // }
        // else
        // {
        //     SDL_Texture* texture = SDL_CreateTextureFromSurface(
        //         gRenderer,
        //         surface
        //     );
            
        //     if (texture == NULL)
        //     {
        //         throw std::runtime_error(
        //             "Couldn't create texture: SDL_Error " + std::string(SDL_GetError())
        //         );
        //     }

        //     // Free surface (no longer needed)
        //     SDL_FreeSurface(surface);
        //     SDL_RenderCopy(gRenderer, texture, NULL, NULL);
        //     SDL_DestroyTexture(texture);
        // }

        // TextureCache textureCache(ROOT_PATH / "graphics", gRenderer);
        // SDL_RenderCopy(gRenderer, textureCache.getTexture(TextureId::SPRITE_FRONT), NULL, NULL);
        
        // Update window
        SDL_RenderPresent(gRenderer);

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