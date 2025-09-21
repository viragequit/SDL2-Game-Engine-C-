#ifndef BIGEYE_H
#define BIGEYE_H

#include "../animation/Animation.h"
#include "MiniEye.h"

class BigEye {
	
	private:
		
		std::string textureID;
		
		Animation* animation;

		int anim_speed;
		
		int xResetPos;

		int yResetPos;
		
		float xPos = 0.0f;
		
		float yPos = 0.0f;

		int center_x = 0;

		int center_y = 0;

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
		
		MiniEye* mini_eye_array[8];

		float orbitA = 50.0f;     // horizontal radius (ellipse major axis)
		float orbitB = 30.0f;     // vertical radius (ellipse minor axis)
		float ellipseRotation = 0.0f; // additional rotation of whole ellipse (radians)
		
		void play_animations(float dT);
		
		void move(float dT);

		bool checkCollision(SDL_Rect tile);
		
	public:
		
		BigEye(std::string id, int x, int y, int w, int h, int s = 1);
		
		BigEye();
		
		~BigEye();
		
		void draw();
		
		void destroy();
		
		void update(float dT);
		
		enum animations {
			
			TURN = 0
		};
};

#endif
