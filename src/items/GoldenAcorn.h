#ifndef GOLDENACORN_H
#define GOLDENACORN_H

#include "../animation/Animation.h"
#include "../tilemap/Tilemap.h"

class GoldenAcorn {
	
	private:

		std::string textureID;
		
		Animation* animation;

		SDL_Rect collision_box;

		int xPos;

		int yPos;

		int width;

		int height;

		int scl;
		
	public:
		
		GoldenAcorn(std::string id, int x, int y, int w, int h, int scale = 1);
		
		GoldenAcorn();
		
		~GoldenAcorn();
		
		void draw();
		
		void destroy();
		
		void update(float dT);
};

#endif