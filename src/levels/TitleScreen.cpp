#include "TitleScreen.h"
#include "../engine/Engine.h"
#include "../graphics/TextureManager.h"
#include "../input/Input.h"
#include "../timer/Timer.h"
#include <iostream>


TitleScreen::TitleScreen(float s) {

	scale = s;

	draw_intro = true;

	show_presents = true;

	show_gap = true;

	show_gap_two = false;

	show_create = false;

	display_time = 2.0f;

	gap_time = 3.0f;

	has_started = false;

	start_game = true;

	exit_game = false;


	TextureManager::getInstance()->load("canvas", "assets/sprites/titleScreen/canvas.png");

	TextureManager::getInstance()->load("presents", "assets/sprites/titleScreen/presents.png");

	TextureManager::getInstance()->load("logo_options", "assets/sprites/titleScreen/logo_and_options.png");

	TextureManager::getInstance()->load("title_screen", "assets/sprites/titleScreen/parallax_background.png");

	TextureManager::getInstance()->load("arrow", "assets/sprites/titleScreen/arrow.png");

	TextureManager::getInstance()->loadStreaming("grass", "assets/sprites/pseudo_sprites/grass.png");

	arrow = new SelectArrow("arrow", 40, 122, 16, 16);

	plane = new AffinePlane("grass", 128, 0, 108, 384, 108);
}

TitleScreen::TitleScreen() {
	
	
}


TitleScreen::~TitleScreen() {
	
	destroy();
}


void TitleScreen::draw() {

	
	if (has_started == false) {

		TextureManager::getInstance()->draw("title_screen", 0, 0);

		plane->draw();

		TextureManager::getInstance()->draw("logo_options", 0, 0);

		arrow->draw();
	}

	if (show_gap == true) {

		TextureManager::getInstance()->draw("canvas", 0, 0);
	}
	
	if (draw_intro == true) {
		
		if (show_presents == true) {

			TextureManager::getInstance()->draw("presents", Engine::getInstance()->getWidth() / 2 - 52, Engine::getInstance()->getHeight() / 2 - 10);
		}
	}
}


void TitleScreen::destroy() {

	delete arrow;

	delete plane;

	std::cout << "Title Screen deleted." << std::endl;
}


void TitleScreen::control(float dT) {

	if (Engine::getInstance()->joystickConnected() == false) {

		// if (Input::getInstance()->getKeyDown(SDL_SCANCODE_RETURN)) {

		// 	draw_intro = false;

		// 	show_create = true;
		// }

		//key press W
		if (Input::getInstance()->getKeyDown(SDL_SCANCODE_W)) {
			
			arrow->setPosY(122);

			start_game = true;

			exit_game = false;
		}
		
		//key release W
		if (Input::getInstance()->getKeyUp(SDL_SCANCODE_W)) {
			
			
		}
		
		//key press S
		if (Input::getInstance()->getKeyDown(SDL_SCANCODE_S)) {
			
			arrow->setPosY(138);

			start_game = false;

			exit_game = true;
		}
		
		//key release S
		if (Input::getInstance()->getKeyUp(SDL_SCANCODE_S)) {
			
			
		}


		//start or exit game
		if (Input::getInstance()->getKeyDown(SDL_SCANCODE_RETURN)) {
			
			if (start_game) {

				show_create = false;

				draw_intro = false;

				has_started = true;
			}

			if (exit_game) {

				Engine::getInstance()->quit();
			}
		}
	}

	else {

		//Run Left
		if (Input::getInstance()->getHatDown(SDL_HAT_UP)) {
			
			arrow->setPosY(122);

			start_game = true;

			exit_game = false;
		}
		
		//key release left
		if (Input::getInstance()->getHatUp(SDL_HAT_UP)) {
			
			
		}
		
		//Run Right
		if (Input::getInstance()->getHatDown(SDL_HAT_DOWN)) {
			
			arrow->setPosY(138);

			start_game = false;

			exit_game = true;
		}
		
		//key release right
		if (Input::getInstance()->getHatUp(SDL_HAT_DOWN)) {
			
			
		}

		if (Input::getInstance()->getButtonDown(2) && draw_intro == false) {

			if (start_game) {

				show_create = false;

				//draw_intro = false;

				has_started = true;
			}

			if (exit_game) {

				Engine::getInstance()->quit();
			}
		}
	}
}


void TitleScreen::playIntro(float dT) {

	if (draw_intro == true) {

		if (stop_watch.isStarted() == false) {

			stop_watch.start();
		}

		if (show_presents == true) {

			if ((stop_watch.getTicks() / 1000.0f) >= display_time) {

				show_presents = false;

				show_gap = true;

				//stop_watch.stop();
			}
		}

		//maybe insert a timed gap between each image to emphasize the music
		if (show_gap == true) {

			if ((stop_watch.getTicks() / 1000.0f) >= gap_time) {
				
				show_gap = false;

				show_create = true;

				draw_intro = false;

				stop_watch.stop();
			}
		}
	}

	// if (show_create == true) {
		
	// 	if ((stop_watch.getTicks() / 1000) == display_time) {
			
	// 		show_create = false;

	// 		show_gap_two = true;

	// 		stop_watch.stop();
	// 	}
	// }
}


bool TitleScreen::getHasStarted() {

	return has_started;
}


//Update all things TitleScreen related (movement, animation)
void TitleScreen::update(float dT) {
	
	playIntro(dT);

	if (show_create) {

		control(dT);
	}
		
	arrow->update(dT);

	plane->update(dT);
	
	//std::cout << "Time: " << stop_watch.getTicks() / 1000.0f << std::endl;

	//std::cout << show_create << std::endl;
}