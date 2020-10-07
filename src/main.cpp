#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "texture_id.h"
#include "texture_cache.h"
#include "map.h"
#include "tile_type.h"

// Path to project directory root
const boost::filesystem::path ROOT_PATH("/home/stefan/Cpp-Adventure-2");
// Path to graphics directory
boost::filesystem::path GRAPHICS_PATH = ROOT_PATH / "graphics";

// Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 512;
// TODO: I WOULD LIKE TO INCREASE TILE WIDTH TO 64X64 (BETTER RESOLUTION)
const int TILE_WIDTH_PX = 32;

// Starts up SDL and creates window
bool init();
// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window* gWindow = NULL;
// The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

int tileRow = 5;
int tileCol = 5;


int main(int argc, char* args[])
{
    if (!init())
    {
        std::cout << "Failed to initialize" << std::endl;;
        exit(1);
    }

    TextureCache textureCache(GRAPHICS_PATH);
    Map map = Map::fromFile(ROOT_PATH / "map.txt");

    bool quit = false;
    SDL_Event next_event;
    // Main loop
    while (!quit)
    {
        //Handle events on queue
        while(SDL_PollEvent(&next_event) != 0)
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
                        if (tileRow > 1)
                        {
                            tileRow -= 1;
                        }
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        std::cout << "Pressed the <DOWN> key" << std::endl;
                        if (tileRow < map.numRows)
                        {
                            tileRow += 1;
                        }
                        break;
                    }
                    case SDLK_LEFT:
                    {
                        std::cout << "Pressed the <LEFT> key" << std::endl;
                        if (tileCol > 0)
                        {
                            tileCol -= 1;
                        }
                        break;
                    }
                    case SDLK_RIGHT:
                    {
                        std::cout << "Pressed the <RIGHT> key" << std::endl;
                        if (tileCol < map.numCols - 1)
                        {
                            tileCol += 1;
                        }
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }
    
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
        // Draw tiles
        SDL_Rect source_rect = {0, 0, TILE_WIDTH_PX, TILE_WIDTH_PX};
        SDL_Rect dest_rect;
        for (int i = 0; i < map.numRows; i++)
        {
            for (int j = 0; j < map.numCols; j++)
            {
                dest_rect.x = j * TILE_WIDTH_PX;
                dest_rect.y = i * TILE_WIDTH_PX;
                // Look up the TextureId for this tile
                TextureId tile_texture = getTileTextureId(map.mapTiles[i][j]);

                SDL_BlitSurface(
                    textureCache.getTexture(tile_texture), 
                    &source_rect, 
                    gScreenSurface, 
                    &dest_rect
                );
            }
        }

        // Draw sprite image.
        // Make the image bottom line up with the tile the sprite is on.
        SDL_Surface* sprite_img = textureCache.getTexture(TextureId::SPRITE_FRONT);
        source_rect = {
            0,
            0,
            sprite_img->w,
            sprite_img->h
        };
        dest_rect.x = tileCol * TILE_WIDTH_PX;
        dest_rect.y = tileRow * TILE_WIDTH_PX - sprite_img->h;
        SDL_BlitSurface(sprite_img, &source_rect, gScreenSurface, &dest_rect);
        
        // Update surface
        SDL_UpdateWindowSurface(gWindow);
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