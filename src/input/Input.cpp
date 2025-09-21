#include <iostream>
#include "Input.h"
#include "../engine/Engine.h"


Input* Input::instance = NULL;


Input::Input() {
	
	keyStates = SDL_GetKeyboardState(NULL);
}


Input::~Input() {
	
	
}


void Input::listen() {
	
	while(SDL_PollEvent(&e)) {
		
		if (e.type == SDL_QUIT) {
			
			Engine::getInstance()->quit();
		}
		
		if (e.type == SDL_KEYDOWN) {
			
			keyDown();
		}
		
		if (e.type == SDL_KEYUP) {
			
			keyUp();
		}

		if (e.type == SDL_JOYBUTTONDOWN) {
			
			//controller one
			if (e.jbutton.which == 0) {
				
				int button = (int)e.jbutton.button;

				joystickButtonStates[button] = 1;

				//std::cout << button << std::endl;
			}
		}

		if (e.type == SDL_JOYBUTTONUP) {

			//controller one
			if (e.jbutton.which == 0) {

				int button = (int)e.jbutton.button;

				joystickButtonStates[button] = 0;
				
				//std::cout << (int)e.jbutton.button << std::endl;
			}
		}

		if (e.type == SDL_JOYHATMOTION) {
			//controller one
				if (e.jhat.which == 0) {
					
					int hatIndex = (int)e.jhat.hat;

					int hatState = e.jhat.value;

					joystickHatStates[hatIndex] = hatState;
				}
		}
	}
}

SDL_Event Input::getEvent() {
	
	return e;
}


void Input::keyUp() {
	
	keyStates = SDL_GetKeyboardState(NULL);
}

void Input::keyDown() {
	
	keyStates = SDL_GetKeyboardState(NULL);
}


bool Input::getKeyDown(SDL_Scancode key) {
	
	if (keyStates[key] == 1) {
		
		return true;
	}
	
	else {
		
		return false;
	}
}

bool Input::getKeyUp(SDL_Scancode key) {
	
	if (keyStates[key] == 0) {
		
		return true;
	}
	
	else {
		
		return false;
	}
}


bool Input::getButtonDown(int button) {
	
	if (joystickButtonStates[button] == 1) {

		return true;
	}

	else {

		return false;
	}
}

bool Input::getButtonUp(int button) {
	
	if (joystickButtonStates[button] == 0) {

		return true;
	}

	else {

		return false;
	}
}


bool Input::getHatDown(int hatDirection) {
	
	int hatState = joystickHatStates[0];

	if ((hatState & hatDirection) == hatDirection) {

		return true;
	}

	else {

		return false;
	}
}

bool Input::getHatUp(int hatDirection) {
	
	int hatState = joystickHatStates[0];

	if ((hatState & hatDirection) == 0) {

		return true;
	}

	else {

		return false;
	}
}