#ifndef Input_H
#define Input_H

//#include "../SDL2/SDL.h"
#include "../engine/Engine.h"


class Input {
	
	private:
		
		Input();
		
		~Input();
		
		static Input* instance;
		
		void keyUp();
		
		void keyDown();
		
		const Uint8* keyStates;

		int numButtons = Engine::getInstance()->getNumJoystickButtons();

		//potentially make dynamic array in future (varying button amount)
		int joystickButtonStates[14];

		int joystickHatStates[14];
		
		SDL_Event e;
		
	public:
		
		static Input* getInstance() {
			
			if (instance == NULL) {
				
				instance = new Input();
			}
			
			return instance;
		}
		
		void listen();
		
		SDL_Event getEvent();
		
		bool getKeyDown(SDL_Scancode key);
		
		bool getKeyUp(SDL_Scancode key);

		bool getButtonDown(int button);

		bool getButtonUp(int button);

		bool getHatDown(int hatDirection);

		bool getHatUp(int hatDirection);
};

#endif