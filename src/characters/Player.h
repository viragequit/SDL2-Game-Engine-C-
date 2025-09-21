#ifndef PLAYER_H
#define PLAYER_H

#include "../animation/Animation.h"
#include "../tilemap/Tilemap.h"

class Player {
	
	private:
		
		std::string textureID;
		
		Animation* animation;

		Tilemap* curr_map;

		int map_size;

		int anim_speed;
		
		int xResetPos;

		int yResetPos;
		
		float xPos = 0.0f;
		
		float yPos = 0.0f;

		int adjustedX = 0;

		int adjustedY = 0;
		
		float xVel = 0.0f;
		
		float yVel = 0.0f;
		
		float acceleration = 0.0f;
		
		float deceleration = 0.0f;
		
		float max_acceleration = 0.0f;
		
		float gravity = 0.0f;

		float jump_gravity = 0.0f;

		float fall_gravity = 0.0f;
		
		float terminal_yVel = 0.0f;
		
		float jump_height = 0.0f;

		float min_jump_height = 0.0f;

		float run_jump_height = 0.0f;

		float walk_jump_height = 0.0f;
		
		int width;
		
		int height;
		
		int scale;
		
		int collision_offset_x;

		int collision_offset_y;
		
		SDL_Rect collision_box;

		SDL_Rect feet;
		
		bool facing_right;

		bool touches_floor;

		bool touches_wall;
		
		bool is_grounded;

		bool is_running;
		
		bool is_jumping;
		
		bool is_falling;
		
		bool is_crouching;
		
		bool can_jump;

		bool jump_button_released;


		// int curr_tile_x;
		// int curr_tile_y;
		// int curr_feet_tile_x;
		// int curr_feet_tile_y;

		int collision_tiles_x[12];
		int collision_tiles_y[12];
		
		void play_animations(float dT);
		
		void move(float dT);
		
		void control(float dT);

		void updateCollision();

		bool checkCollision(SDL_Rect tile);
		
		bool touchesWall();

		bool checkFloor(SDL_Rect tile);
		
		bool touchesFloor();
		
	public:
		
		Player(std::string id, int x, int y, int w, int h, int s = 1);
		
		Player();
		
		~Player();
		
		void setMap(Tilemap* tilemap);
		
		void draw();
		
		void destroy();
		
		void update(float dT);
		
		enum animations {
			
			IDLE = 0,
			WALK = 1,
			RUN = 2,
			JUMP = 3,
			FALL = 4,
			ATTACK = 5,
			CROUCH = 6,
			CRAWL = 7
		};
};

#endif
