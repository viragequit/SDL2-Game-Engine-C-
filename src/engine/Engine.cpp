#include "Engine.h"
#include "../timer/Timer.h"
#include "../input/Input.h"
#include "../graphics/TextureManager.h"
#include "../levels/TitleScreen.h"
#include "../levels/TestLevel.h"
#include "../menus/PauseMenu.h"
#include "../debug/ControllerDisplay.h"

#include <iostream>



Engine* Engine::instance = NULL;

TitleScreen* ts = NULL;

TestLevel* test_level = NULL;

PauseMenu* pause = NULL;

ControllerDisplay* cd = NULL;


Engine::Engine() {
	
	success = true;
}


Engine::~Engine() {
	
	
}


bool Engine::initialize() {

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
		
		std::cout << "Failed to initialize! SDL Error: " << SDL_GetError() << std::endl;
		
		success = false;
	}
	
	else {
		
		Uint32 screen_flags = SDL_WINDOW_ALLOW_HIGHDPI;
		
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
		
		window = SDL_CreateWindow("Chinn-gine 0.1.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, screen_flags);
		
		if (window == NULL) {
			
			std::cout << "Failed to create window! SDL Error: " << SDL_GetError() << std::endl;
			
			success = false;
		}
		
		else {
			
			//Default Window Size (1280 x 720)
			//SDL_SetWindowSize(window, 1536, 864);
			SDL_SetWindowSize(window, 1920, 1080);
			SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
			
			//Show mouse cursor
			SDL_ShowCursor(SDL_ENABLE);
			
			//renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			
			if (renderer == NULL) {
				
				std::cout << "Failed to create renderer! SDL Error: " << SDL_GetError() << std::endl;
				
				success = false;
			}
			
			else {
				
				SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
				
				int imgFlags = IMG_INIT_PNG;
				
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					
					std::cout << "Failed to initialize SDL_image! SDL_image Error: " << IMG_GetError() << std::endl;
					
					success = false;
				}
				
				if (TTF_Init() == -1) {
					
					std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
					
					success = false;
				}
			}

			if (SDL_NumJoysticks() < 1) {

				std::cout << "Warning: No joysticks connected!\n" << std::endl;
			}

			else {

				joystick = SDL_JoystickOpen(0);

				if (joystick == NULL) {

					std::cout << "Warning: Unable to open game controller!" << std::endl;
				}

				else  {

					std::cout << "Controller Name: " << SDL_JoystickName(joystick) << std::endl;
					std::cout << "Number of Axes: " << SDL_JoystickNumAxes(joystick) << std::endl;
					std::cout << "Number of Buttons: " << SDL_JoystickNumButtons(joystick) << std::endl;
					std::cout << "Number of D-Pads: " << SDL_JoystickNumHats(joystick) << std::endl;
				}
			}
		}
		
		SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
		SDL_GetCurrentDisplayMode(0, &displayMode);
		desktop_width = displayMode.w;
		desktop_height = displayMode.h;
	}
	
	
	/* Load levels, images and create characters here ------------------------------------- */
	
	TextureManager::getInstance()->load("logo", "assets/sprites/misc/CS_Logo.png");
	
	TextureManager::getInstance()->load("copyright", "assets/sprites/copyright.png");

	ts = new TitleScreen(1);

	test_level = new TestLevel(true);

	pause = new PauseMenu(1);

	cd = new ControllerDisplay(256, 148);
	
	return success;
}


bool Engine::destroy() {
	
	//delete all textures
	TextureManager::getInstance()->destroy();
	
	//delete game objects
	ts->destroy();
	pause->destroy();
	test_level->destroy();
	
	delete ts;

	delete test_level;

	delete pause;

	delete cd;


	SDL_JoystickClose(joystick);
	
	joystick = NULL;
	
	SDL_DestroyRenderer(renderer);
	
	SDL_DestroyWindow(window);
	
	window = NULL;
	
	renderer = NULL;
	
	IMG_Quit();
	
	SDL_Quit();
}


bool Engine::isRunning() {
	
	return success;
}


void Engine::quit() {
	
	success = false;
}


void Engine::update() {
	
	float dT = Timer::getInstance()->getDeltaTime();
	
	if (ts->getHasStarted() == true) {

		pause->update(dT);
	}

	if (pause->isPaused() == false) {

		test_level->update(dT);
	}

	if (ts->getHasStarted() == false) {

		ts->update(dT);
	}
}


void Engine::render() {
	
	SDL_RenderClear(renderer);
	
	
	//draw levels here
	test_level->draw();

	//controller testing
	//cd->draw();
	
	//Player probably should be drawn on top of most other assets (maybe not the tile map)
	
	
	//Menu Testing---------------------------------
	

	
	//---------------------------------------------
	
	//90 IS SWEET SPOT (1/8 OF VERTICAL RESOLUTION) canvas the size of half of current resolution_y plus 1/8 of current resolution_y
	//(720 = 450, 1080 = 675) !!!!! probably don't have to worry since resolution scaling is handled automatically by SDL !!!!!
	
	
	//TextureManager::getInstance()->draw("logo", 16, 16, SDL_FLIP_NONE, 1);
	//TextureManager::getInstance()->draw("copyright", 184, 16, SDL_FLIP_NONE, 1);


	pause->draw();

	ts->draw();
	
	
	SDL_RenderPresent(renderer);
}


void Engine::pollEvents() {
	
	Input::getInstance()->listen();
}


SDL_Window* Engine::getWindow() {
	
	return window;
}


SDL_Renderer* Engine::getRenderer() {
	
	return renderer;
}


int Engine::getNumJoystickButtons() {

	return SDL_JoystickNumButtons(joystick);
}


bool Engine::joystickConnected() {

	if (joystick == NULL) {

		return false;
	}

	else {

		return true;
	}
}