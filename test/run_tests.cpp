#include <gtest/gtest.h>
#include <SDL2/SDL.h>
#include <boost/filesystem.hpp>
#include "game_engine.h"
#include "drop.h"


// Path to project directory root
const boost::filesystem::path ROOT_PATH("/home/stefan/Cpp-Adventure-2");

// Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 512;


TEST(test, hello_world)
{
    // Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::runtime_error(
            std::string("SDL could not initialize! SDL_Error: ") +
            std::string(SDL_GetError())
        );
	}

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        throw std::runtime_error(
            std::string("SDL_image could not initialize! SDL_image Error: ") +
            std::string(IMG_GetError())
        );
    }
    
    // TODO: SEPARATION OF ENGINE AND SDL ESPECIALLY IMPORTANT IN ORDER
    // TO RUN TESTS WITHOUT HAVING TO CREATE A WINDOW EACH TIME
    SDL_Window* gWindow = SDL_CreateWindow(
        "Stefan's C++ Game", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        SDL_WINDOW_HIDDEN
    );

    if (gWindow == NULL)
    {
        throw std::runtime_error(
            std::string("Window could not be created! SDL_Error: ") +
            std::string(SDL_GetError())
        );
    }

    //Create renderer for window
    SDL_Renderer* gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL)
    {
        throw std::runtime_error(
            std::string("Renderer could not be created! SDL Error: ") +
            std::string(SDL_GetError())
        );
    }

    // Create GameEngine
    GameEngine gameEngine(
        ROOT_PATH,
        gRenderer,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    );

    std::shared_ptr<GameContext> game_context = 
        gameEngine.getGameContextForTesting();
    std::shared_ptr<Map> map = 
        gameEngine.getMapForTesting();

    auto item = ItemFactory::createItem(
        game_context.get(),
        ItemType::PICKAXE
    );

    auto drop = std::make_shared<Drop>(
        game_context.get(),
        item,
        SDL_Rect{0, 0, 32, 32}
    );

    ASSERT_EQ(item, drop->getItem());

    drop.reset();

    ASSERT_EQ(ItemType::PICKAXE, item->getItemType());
    ASSERT_EQ(TextureId::PICKAXE_ITEM, item->getTextureId());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}