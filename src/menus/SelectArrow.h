#ifndef SELECTARROW_H
#define SELECTARROW_H

#include "../animation/Animation.h"

class SelectArrow {
	
	private:
		
		std::string textureID;
		
		Animation* animation;
		
		int xPos;
		
		int yPos;
		
		int width;
		
		int height;
		
		int scale;
		
		void play_animations();
		
	public:
		
		SelectArrow(std::string id, int x, int y, int w, int h, int s = 1);
		
		SelectArrow();
		
		~SelectArrow();
		
		void draw();
		
		void destroy();

		void setPosX(int);

		void setPosY(int);
		
		void update(float dT);
		
		enum animations {
			
			CHOOSE = 0,
			SELECT = 1
		};
};

#endif
