#include "PauseMenu.h"
#include "../engine/Engine.h"
#include "../graphics/TextureManager.h"
#include "../input/Input.h"
#include "../camera/Camera.h"
#include "../timer/Timer.h"
#include <iostream>


PauseMenu::PauseMenu(float s) {

	scale = s;

	is_paused = false;

	can_toggle = true;

	TextureManager::getInstance()->load("p_canvas", "assets/sprites/pauseMenu/canvas.png");

	TextureManager::getInstance()->load("p_canvas_border", "assets/sprites/pauseMenu/canvas_border.png");

	TextureManager::getInstance()->load("info", "assets/sprites/pauseMenu/pause_menu.png");

	TextureManager::getInstance()->setAlpha("p_canvas", 220);
}

PauseMenu::PauseMenu() {
	
	
}


PauseMenu::~PauseMenu() {
	
	
}


bool PauseMenu::isPaused() {

	return is_paused;
}


void PauseMenu::draw() {

	if (is_paused == true) {
		int centerX = Engine::getInstance()->getWidth() / 2;
		int centerY = Engine::getInstance()->getHeight() / 2;

		int p_canvas_center_x = TextureManager::getInstance()->getWidth("p_canvas") / 2;
		int p_canvas_center_y = TextureManager::getInstance()->getHeight("p_canvas") / 2;

		int p_canvas_border_center_x = TextureManager::getInstance()->getWidth("p_canvas_border") / 2;
		int p_cavnas_border_center_y = TextureManager::getInstance()->getHeight("p_canvas_border") / 2;

		int info_center_x = TextureManager::getInstance()->getWidth("info") / 2;
		int info_center_y = TextureManager::getInstance()->getHeight("info") / 2;

		TextureManager::getInstance()->draw("p_canvas", centerX - p_canvas_center_x, centerY - p_canvas_center_y, SDL_FLIP_NONE, 1);
		TextureManager::getInstance()->draw("p_canvas_border", centerX - p_canvas_center_x, centerY - p_canvas_center_y, SDL_FLIP_NONE, 1);
		TextureManager::getInstance()->draw("info", centerX - info_center_x, centerY - info_center_y, SDL_FLIP_NONE, 1);
	}
}


void PauseMenu::destroy() {
	
	std::cout << "Pause Menu deleted." << std::endl;
}


void PauseMenu::control(float dT) {

	if (Engine::getInstance()->joystickConnected() == false) {

		if (can_toggle == true) {

			if (Input::getInstance()->getKeyDown(SDL_SCANCODE_ESCAPE)) {
				
				can_toggle = false;
				is_paused = !is_paused;
			}
		}

		if (Input::getInstance()->getKeyUp(SDL_SCANCODE_ESCAPE)) {

			can_toggle = true;
		}
	}

	else {

		if (can_toggle == true) {

			if (Input::getInstance()->getButtonDown(9)) {
				
				can_toggle = false;
				is_paused = !is_paused;
			}
		}

		if (Input::getInstance()->getButtonUp(9)) {

			can_toggle = true;
		}
	}
}


//Update all things PauseMenu related (movement, animation)
void PauseMenu::update(float dT) {

	control(dT);

	//std::cout << is_paused << std::endl;
}