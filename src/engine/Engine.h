#ifndef ENGINE_H
#define ENGINE_H

#include "../SDL2/SDL.h"
#include "../SDL2/SDL_image.h"
#include "../SDL2/SDL_ttf.h"


class Engine {
	
	private:
		
		static Engine* instance;
		
		Engine();
		
		~Engine();
		
		SDL_Window* window = NULL;
		
		SDL_Renderer* renderer = NULL;
		
		SDL_DisplayMode displayMode;

		SDL_Joystick* joystick = NULL;
		
		//Desktop resolution values
		int desktop_width;
		int desktop_height;
		
		bool success;
		
		//Game resolution values (multiples of 320 and 180) max 2560x1440
		//const int WIDTH = 768;
		//const int HEIGHT = 432;

		const int WIDTH = 384;
		const int HEIGHT = 216;
		
	public:
		
		static Engine* getInstance() {
			
			if (!instance) {
				
				instance = new Engine();
			}
			
			return instance;
		}
		
		bool initialize();
		
		bool destroy();
		
		bool isRunning();
		
		void quit();
		
		void update();
		
		void render();
		
		void pollEvents();
		
		void changeResolution(int i);
		
		int getResX();
		
		int getResY();
		
		SDL_Window* getWindow();
		
		SDL_Renderer* getRenderer();

		int getNumJoystickButtons();

		bool joystickConnected();
		
		int getWidth() {
			
			return WIDTH;
		}
		
		int getHeight() {
			
			return HEIGHT;
		}
};

#endif
