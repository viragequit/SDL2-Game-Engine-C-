#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include "../SDL2/SDL.h"


class Animation {
	
	private:
		
		int sprite_row;
		
		int sprite_frame;
		
		int animation_speed;
		
		int frame_count;
		
		std::string textureID;
		
		SDL_RendererFlip sprite_flip;
		
	public:
		
		Animation();
		
		~Animation();
		
		void setProperties(std::string id, int row, int f_count, int anim_speed, SDL_RendererFlip flip = SDL_FLIP_NONE);
		
		void draw(int x, int y, int width, int height, int scale = 1);
		
		//void drawRepeat(int x, int y, int width, int height, int row, int col, float scale = 1.0);
		
		void update(float dT);
};

#endif
