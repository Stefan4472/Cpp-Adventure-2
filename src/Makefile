#OBJS specifies which files to compile as part of the project
OBJS = texture_id.cpp texture_cache.cpp tile_type.cpp map.cpp sprite.cpp spritesheet.cpp sprite_model.cpp player_sprite.cpp game_context.cpp game_engine.cpp main.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = run

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) -std=c++11 -lSDL2 -lSDL2_image -lboost_system -lboost_filesystem -o ../build/$(OBJ_NAME)