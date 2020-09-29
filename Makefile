#OBJS specifies which files to compile as part of the project
OBJS = main.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = run

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) -lSDL2 -lSDL2_image -o $(OBJ_NAME)