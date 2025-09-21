#ifndef MINIEYE_H
#define MINIEYE_H

#include "../animation/Animation.h"

class MiniEye {
	
	private:
		
		std::string textureID;
		
		Animation* animation;

		int anim_speed;
		
		float xPos = 0.0f;
		
		float yPos = 0.0f;

		float angle = 0.0f;

		int adjustedX = 0;

		int adjustedY = 0;
		
		float xVel = 0.0f;
		
		float yVel = 0.0f;

		float acceleration = 0.0f;

		float deceleration = 0.0f;
		
		int width;
		
		int height;
		
		int scale;
		
		int collision_offset_x;

		int collision_offset_y;
		
		SDL_Rect collision_box;
		
		bool facing_right;

		int collision_tiles_x[12];
		int collision_tiles_y[12];
		
		void play_animations(float dT);

		bool checkCollision(SDL_Rect tile);
		
	public:
		
		MiniEye(std::string id, int x, int y, int w, int h, int s = 1);
		
		MiniEye();
		
		~MiniEye();

		void setAngle(float a);

		float getAngle();

		void setAcceleration(float s);

		float getAcceleration();
		
		void draw();

		void move(float x, float y, float dT);
		
		void destroy();
		
		void update(float dT);
		
		enum animations {
			
			FLY = 0
		};
};

#endif
