#OBJS specifies which files to compile as part of the project
OBJS = \
	texture_id.cpp \
	texture_cache.cpp \
	map.cpp \
	sprite.cpp \
	spritesheet.cpp \
	sprite_model.cpp \
	input_handler.cpp \
	game_renderer.cpp \
	player_sprite.cpp \
	game_context.cpp \
	game_engine.cpp \
	tiles/tile_type.cpp \
	tiles/tile.cpp \
	tiles/tile_factory.cpp \
	tiles/grass_tile.cpp \
	tiles/sand_tile.cpp \
	tiles/dirt_tile.cpp \
	tiles/stone_tile.cpp \
	main.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = run

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) -std=c++11 -lSDL2 -lSDL2_image -lboost_system -lboost_filesystem -Itiles -I. -o ../build/$(OBJ_NAME)