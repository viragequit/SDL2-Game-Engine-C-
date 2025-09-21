#OBJS specifies which files to compile as part of the project
#OBJS_ONE = main.cpp src/engine/Engine.cpp src/timer/Timer.cpp src/input/Input.cpp src/graphics/TextureManager.cpp

#OBJS_TWO = src/animation/Animation.cpp src/camera/*.cpp src/tilemap/*.cpp src/props/*cpp src/characters/*.cpp src/levels/*.cpp
#src/tilemap/*.cpp

OBJS = main.o Engine.o Timer.o StopWatch.o Input.o TextureManager.o Animation.o Camera.o Tilemap.o ParallaxLayer.o AffinePlane.o TitleScreen.o TestLevel.o PauseMenu.o SelectArrow.o Player.o BigEye.o MiniEye.o GoldenAcorn.o ControllerDisplay.o DeathExplosion.o

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\SDL_Development\SDL2\include\SDL2 -IC:\SDL_Development\mingw_SDL2_image_32bit\include\SDL2 -IC:\SDL_Development\mingw_SDL2_ttf_32bit\include\SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\SDL_Development\SDL2\lib -LC:\SDL_Development\mingw_SDL2_image_32bit\lib -LC:\SDL_Development\mingw_SDL2_ttf_32bit\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem, -mwindows -> windows gets rid of the console window
COMPILER_FLAGS = -w #-mwindows

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

#EXEC specifies the name of our executable
EXEC = ChinnsleysQuest.exe

#This is the target that compiles our executable
#all: $(OBJS_ONE) $(OBJS_TWO)
	#$(CC) $(OBJS_ONE) $(OBJS_TWO) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXEC)

all: Game

Game: $(OBJS)
	$(CC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(OBJS) $(LINKER_FLAGS) -o $(EXEC)

main.o: main.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/engine -I ./src/timer $(COMPILER_FLAGS) -c main.cpp

Engine.o: ./src/engine/Engine.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/engine -I ./src/timer -I ./src/input -I ./src/graphics -I ./src/tilemap -I ./src/characters -I ./src/props $(COMPILER_FLAGS) -c ./src/engine/Engine.cpp

Timer.o: ./src/timer/Timer.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/timer $(COMPILER_FLAGS) -c ./src/timer/Timer.cpp

StopWatch.o: ./src/timer/StopWatch.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/timer $(COMPILER_FLAGS) -c ./src/timer/StopWatch.cpp

Input.o: ./src/input/Input.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/engine -I ./src/input $(COMPILER_FLAGS) -c ./src/input/Input.cpp

TextureManager.o: ./src/graphics/TextureManager.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/engine -I ./src/graphics $(COMPILER_FLAGS) -c ./src/graphics/TextureManager.cpp

Animation.o: ./src/animation/Animation.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/timer -I ./src/graphics -I ./src/animation $(COMPILER_FLAGS) -c ./src/animation/Animation.cpp

Camera.o: ./src/camera/Camera.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/camera $(COMPILER_FLAGS) -c ./src/camera/Camera.cpp

Tilemap.o: ./src/tilemap/Tilemap.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/graphics -I ./src/tilemap $(COMPILER_FLAGS) -c ./src/tilemap/Tilemap.cpp

ParallaxLayer.o: ./src/props/ParallaxLayer.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/props $(COMPILER_FLAGS) -c ./src/props/ParallaxLayer.cpp

AffinePlane.o: ./src/props/AffinePlane.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/props $(COMPILER_FLAGS) -c ./src/props/AffinePlane.cpp

Player.o: ./src/characters/Player.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/input -I ./src/graphics -I ./src/camera -I ./src/characters $(COMPILER_FLAGS) -c ./src/characters/Player.cpp

BigEye.o: ./src/enemies/BigEye.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/graphics -I ./src/enemies $(COMPILER_FLAGS) -c ./src/enemies/BigEye.cpp
	
MiniEye.o: ./src/enemies/MiniEye.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/graphics -I ./src/enemies $(COMPILER_FLAGS) -c ./src/enemies/MiniEye.cpp

GoldenAcorn.o: ./src/items/GoldenAcorn.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/graphics -I ./src/camera -I ./src/items $(COMPILER_FLAGS) -c ./src/items/GoldenAcorn.cpp

TitleScreen.o: ./src/levels/TitleScreen.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/input -I ./src/graphics -I ./src/camera $(COMPILER_FLAGS) -c ./src/levels/TitleScreen.cpp

PauseMenu.o: ./src/menus/PauseMenu.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/input -I ./src/graphics -I ./src/camera $(COMPILER_FLAGS) -c ./src/menus/PauseMenu.cpp

SelectArrow.o: ./src/menus/SelectArrow.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/input -I ./src/graphics -I ./src/camera $(COMPILER_FLAGS) -c ./src/menus/SelectArrow.cpp

TestLevel.o: ./src/levels/TestLevel.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/graphics -I ./src/tilemap -I ./src/characters -I ./src/props $(COMPILER_FLAGS) -c ./src/levels/TestLevel.cpp

ControllerDisplay.o: ./src/debug/ControllerDisplay.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/input -I ./src/graphics $(COMPILER_FLAGS) -c ./src/debug/ControllerDisplay.cpp

DeathExplosion.o: ./src/effects/DeathExplosion.cpp
	$(CC) $(INCLUDE_PATHS) -I ./src/graphics -I ./src/camera $(COMPILER_FLAGS) -c ./src/effects/DeathExplosion.cpp

run:
	$(EXEC)

clean:
	del *.o