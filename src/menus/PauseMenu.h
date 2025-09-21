#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "../animation/Animation.h"
#include "../tilemap/Tilemap.h"

class PauseMenu {
	
	private:
		
		std::string textureID;
		
		Animation* animation;

		float scale;

		bool is_paused;

		bool can_toggle;
		
	public:
		
		PauseMenu(float s = 1.0f);
		
		PauseMenu();
		
		~PauseMenu();
		
		bool isPaused();
		
		void draw();
		
		void destroy();

		void control(float dT);
		
		void update(float dT);
};

#endif
