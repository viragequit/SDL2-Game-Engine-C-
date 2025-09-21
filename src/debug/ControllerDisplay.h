#ifndef CONTROLLERDISPLAY_H
#define CONTROLLERDISPLAY_H

#include "../SDL2/SDL.h"
#include "../engine/Engine.h"


class ControllerDisplay {
	
	private:
		
		int xPos = 0;
		
		int yPos = 0;
		
	public:

		ControllerDisplay(int, int);

		ControllerDisplay();
		
		~ControllerDisplay();

		void draw();
		
		void update(float);
};

#endif
