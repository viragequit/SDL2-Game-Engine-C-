#include "ControllerDisplay.h"
#include "../graphics/TextureManager.h"
#include "../input/Input.h"
#include <iostream>


ControllerDisplay::ControllerDisplay(int x, int y) {
	
	xPos = x;
	yPos = y;

	TextureManager::getInstance()->load("ctrl_none", "assets/sprites/misc/controller_none.png");
	TextureManager::getInstance()->load("ctrl_up", "assets/sprites/misc/controller_up.png");
	TextureManager::getInstance()->load("ctrl_down", "assets/sprites/misc/controller_down.png");
	TextureManager::getInstance()->load("ctrl_left", "assets/sprites/misc/controller_left.png");
	TextureManager::getInstance()->load("ctrl_right", "assets/sprites/misc/controller_right.png");
	TextureManager::getInstance()->load("ctrl_a", "assets/sprites/misc/controller_a.png");
	TextureManager::getInstance()->load("ctrl_b", "assets/sprites/misc/controller_b.png");
	TextureManager::getInstance()->load("ctrl_x", "assets/sprites/misc/controller_x.png");
	TextureManager::getInstance()->load("ctrl_y", "assets/sprites/misc/controller_y.png");
	TextureManager::getInstance()->load("ctrl_select", "assets/sprites/misc/controller_select.png");
	TextureManager::getInstance()->load("ctrl_start", "assets/sprites/misc/controller_start.png");
	TextureManager::getInstance()->load("ctrl_l", "assets/sprites/misc/controller_l.png");
	TextureManager::getInstance()->load("ctrl_r", "assets/sprites/misc/controller_r.png");
}


ControllerDisplay::~ControllerDisplay() {
	
	
}

void ControllerDisplay::draw() {

	TextureManager::getInstance()->draw("ctrl_none", xPos, yPos, SDL_FLIP_NONE, 0.5);

	if (Input::getInstance()->getHatDown(SDL_HAT_UP)) {

		TextureManager::getInstance()->draw("ctrl_up", xPos, yPos, SDL_FLIP_NONE, 0.5);
	}

	if (Input::getInstance()->getHatDown(SDL_HAT_DOWN)) {

		TextureManager::getInstance()->draw("ctrl_down", xPos, yPos, SDL_FLIP_NONE, 0.5);
	}

	if (Input::getInstance()->getHatDown(SDL_HAT_LEFT)) {

		TextureManager::getInstance()->draw("ctrl_left", xPos, yPos, SDL_FLIP_NONE, 0.5);
	}

	if (Input::getInstance()->getHatDown(SDL_HAT_RIGHT)) {

		TextureManager::getInstance()->draw("ctrl_right", xPos, yPos, SDL_FLIP_NONE, 0.5);
	}

	if (Input::getInstance()->getButtonDown(0)) {

		TextureManager::getInstance()->draw("ctrl_y", xPos, yPos, SDL_FLIP_NONE, 0.5);
	}

	if (Input::getInstance()->getButtonDown(1)) {

		TextureManager::getInstance()->draw("ctrl_b", xPos, yPos, SDL_FLIP_NONE, 0.5);
	}

	if (Input::getInstance()->getButtonDown(2)) {

		TextureManager::getInstance()->draw("ctrl_a", xPos, yPos, SDL_FLIP_NONE, 0.5);
	}

	if (Input::getInstance()->getButtonDown(3)) {

		TextureManager::getInstance()->draw("ctrl_x", xPos, yPos, SDL_FLIP_NONE, 0.5);
	}

	if (Input::getInstance()->getButtonDown(4)) {

		TextureManager::getInstance()->draw("ctrl_l", xPos, yPos, SDL_FLIP_NONE, 0.5);
	}

	if (Input::getInstance()->getButtonDown(5)) {

		TextureManager::getInstance()->draw("ctrl_r", xPos, yPos, SDL_FLIP_NONE, 0.5);
	}

	if (Input::getInstance()->getButtonDown(6)) {

		TextureManager::getInstance()->draw("ctrl_l", xPos, yPos, SDL_FLIP_NONE, 0.5);
	}

	if (Input::getInstance()->getButtonDown(7)) {

		TextureManager::getInstance()->draw("ctrl_r", xPos, yPos, SDL_FLIP_NONE, 0.5);
	}

	if (Input::getInstance()->getButtonDown(8)) {

		TextureManager::getInstance()->draw("ctrl_select", xPos, yPos, SDL_FLIP_NONE, 0.5);
	}

	if (Input::getInstance()->getButtonDown(9)) {

		TextureManager::getInstance()->draw("ctrl_start", xPos, yPos, SDL_FLIP_NONE, 0.5);
	}
}

void ControllerDisplay::update(float dT) {
	
	
}
