#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


// Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 512;
// TODO: I WOULD LIKE TO INCREASE TILE WIDTH TO 64X64 (BETTER RESOLUTION)
const int TILE_WIDTH_PX = 32;

// Starts up SDL and creates window
bool init();
// Loads media
bool loadMedia();
// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window* gWindow = NULL;
// The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

SDL_Surface* gSpriteImg = NULL;
SDL_Surface* gGrassTile = NULL;


int main(int argc, char* args[])
{
    if (!init())
    {
        printf("Failed to initialize\n");
        exit(1);
    }
    if (!loadMedia()) 
    {
        printf("Failed to load media\n");
        exit(1);
    }

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
                        printf("Pressed the <UP> key\n");
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        printf("Pressed the <DOWN> key\n");
                        break;
                    }
                    case SDLK_LEFT:
                    {
                        printf("Pressed the <LEFT> key\n");
                        break;
                    }
                    case SDLK_RIGHT:
                    {
                        printf("Pressed the <RIGHT> key\n");
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
        SDL_Rect source_rect = {0, 0, 32, 32};
        SDL_Rect dest_rect;
        for (int i = 0; i < SCREEN_HEIGHT; i += TILE_WIDTH_PX)
        {
            for (int j = 0; j < SCREEN_WIDTH; j += TILE_WIDTH_PX)
            {
                dest_rect.x = j;
                dest_rect.y = i;
                SDL_BlitSurface(
                    gGrassTile, 
                    &source_rect, 
                    gScreenSurface, 
                    &dest_rect
                );
            }
        }
        // Draw sprite image
        SDL_BlitSurface(gSpriteImg, NULL, gScreenSurface, NULL);
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
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
	}
    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
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
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Get window surface
    gScreenSurface = SDL_GetWindowSurface(gWindow);
    return true;
}

bool loadMedia() 
{
    gSpriteImg = IMG_Load("graphics/sprite-front.png");
    if (gSpriteImg == NULL)
    {
        printf("Unable to load image! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    gGrassTile = IMG_Load("graphics/grass-tile.png");
    if (gGrassTile == NULL)
    {
        printf("Unable to load image! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void close()
{
    // Deallocate surface
    SDL_FreeSurface(gSpriteImg);
    gSpriteImg = NULL;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}