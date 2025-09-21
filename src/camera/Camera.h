#ifndef CAMERA_H
#define CAMERA_H

#include "../SDL2/SDL.h"
#include "../engine/Engine.h"


class Camera {
	
	private:
		
		static Camera* instance;
		
		Camera();
		
		~Camera();
		
		SDL_Rect camera = {0, 0, Engine::getInstance()->getWidth(), Engine::getInstance()->getWidth()};
		
		int width = camera.w;
		
		int height = camera.h;
		
		int xPos = 0;
		
		int yPos = 0;
		
		int xMin = 0;
		
		int xMax = 0;
		
		int yMin = 0;
		
		int yMax = 0;
		
	public:
		
		static Camera* getInstance() {
			
			if (instance == NULL) {
				
				instance = new Camera();
			}
			
			return instance;
		}
		
		int getWidth();
		
		int getHeight();
		
		int getXPos();
		
		int getYPos();
		
		void setPosition(int, int, int, int);
		
		void setBounds(int, int, int, int);
		
		void update(float);
};

#endif
