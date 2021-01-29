OBJS = revzero.o engine.o resourcemanager.o globals.o soundmanager.o shotemitter.o player.o boid.o starfield.o titlestate.o playstate.o shot.o explosion.o

CC = g++

# smallest = -s -Os -fno-exceptions
COMPILER_FLAGS = -Wall -Werror -std=c++11 -s -Os -fno-exceptions -msse3
COMPILER_FLAGS_ALT = -Wall -Werror -std=c++11 -s -Os

# sunvox: -ldl
LINKER_FLAGS = -lSDL2 -lGL -lGLEW -ldl

OBJ_NAME = app

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	./$(OBJ_NAME)

boid.o : boid.cpp
	$(CC) -c boid.cpp $(COMPILER_FLAGS)

player.o : player.cpp
	$(CC) -c player.cpp $(COMPILER_FLAGS)

shotemitter.o : shotemitter.cpp
	$(CC) -c shotemitter.cpp $(COMPILER_FLAGS)

soundmanager.o : soundmanager.cpp
	$(CC) -c soundmanager.cpp $(COMPILER_FLAGS)

shot.o : shot.cpp
	$(CC) -c shot.cpp $(COMPILER_FLAGS)

explosion.o : explosion.cpp
	$(CC) -c explosion.cpp $(COMPILER_FLAGS)

globals.o : globals.cpp
	$(CC) -c globals.cpp $(COMPILER_FLAGS)

playstate.o : playstate.cpp
	$(CC) -c playstate.cpp $(COMPILER_FLAGS_ALT)

titlestate.o : titlestate.cpp
	$(CC) -c titlestate.cpp $(COMPILER_FLAGS)

starfield.o : starfield.cpp
	$(CC) -c starfield.cpp $(COMPILER_FLAGS)

resourcemanager.o : resourcemanager.cpp
	$(CC) -c resourcemanager.cpp $(COMPILER_FLAGS)

engine.o : engine.cpp
	$(CC) -c engine.cpp $(COMPILER_FLAGS)

revzero.o : revzero.cpp
	$(CC) -c revzero.cpp $(COMPILER_FLAGS)

clean :
	rm -f $(OBJS)
