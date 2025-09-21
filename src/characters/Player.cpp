#include "Player.h"
#include "../engine/Engine.h"
#include "../graphics/TextureManager.h"
#include "../input/Input.h"
#include "../camera/Camera.h"
#include <iostream>
#include <cmath>


Player::Player(std::string id, int x, int y, int w, int h, int s) {
	
	//For y, if not a vertically scrolling level, y is resolution height (x1 to x2, y1 to y2)
	Camera::getInstance()->setBounds(0, 384*7, 0, 216);
	
	animation = new Animation();
	
	textureID = id;
	
	xResetPos = x;

	yResetPos = y;

	xPos = x;
	
	yPos = y;

	adjustedX = x;

	adjustedY = y;
	
	width = w;
	
	height = h;
	
	scale = s;
	
	//physics variables-------------
	acceleration = 0.08f;
	
	deceleration = 0.16f;
	
	max_acceleration = 1.8f;
	
	gravity = 0.3f;

	jump_gravity = 0.15f;

	fall_gravity = 0.28f;
	
	terminal_yVel = 6.2f;
	
	jump_height = 4.8f;

	walk_jump_height = 4.8f;

	run_jump_height = 5.4f;

	min_jump_height = 0.6f;
	//-------------------------------
	
	collision_offset_x = 10;

	collision_offset_y = 2;

	collision_box.x = (adjustedX + collision_offset_x) * scale;

	collision_box.y = (adjustedY + collision_offset_y) * scale;
	
	collision_box.w = (12) * scale;
	
	collision_box.h = (height - collision_offset_y * scale);

	//add second crouching collision box in future
	feet.x = (xPos + collision_offset_x) * scale;
	feet.y = (height + 1) * scale;
	feet.w = 12;
	feet.h = 1;
	
	facing_right = true;

	touches_floor = false;

	touches_wall = false;
	
	is_grounded = false;
	
	is_jumping = true;
	
	is_falling = true;
	
	is_crouching = false;
	
	can_jump = true;

	jump_button_released = true;
	
	//animation->setProperties(textureID, RUN, 8, 100);
}

Player::Player() {
	
	
}


Player::~Player() {
	
	
}


void Player::setMap(Tilemap* tilemap) {
	
	curr_map = tilemap;

	//map_size = curr_map->getMapSize();
}


void Player::draw() {
	
	//make sure in draw functions you account for camera offset!
	float camX = Camera::getInstance()->getXPos();
	
	float camY = Camera::getInstance()->getYPos();
	
	//animation->draw((int)(xPos - camX), (int)(yPos - camY), width, height, scale);

	animation->draw(static_cast<int>(xPos - camX), static_cast<int>(yPos - camY), width, height, scale);
	
	
	//for testing only
	collision_box.x -= static_cast<int>(camX);
	collision_box.y -= static_cast<int>(camY);

	feet.x -= static_cast<int>(camX);
	feet.y -= static_cast<int>(camY);
	
	//SDL_RenderDrawRect(Engine::getInstance()->getRenderer(), &collision_box);

	//SDL_RenderDrawRect(Engine::getInstance()->getRenderer(), &feet);
}


void Player::destroy() {
	
	std::cout << "Player deleted." << std::endl;
	
	delete animation;
}


bool Player::checkCollision(SDL_Rect tile) {

	//bottom intersects top of tile
	if (collision_box.y + collision_box.h <= tile.y) { //collisionMap[i]

		return false;
	}
	
	//top intersects bottom of tile
	if (collision_box.y >= tile.y + tile.h) {
		
		return false;
	}
	
	//right intersects left of tile
	if (collision_box.x + collision_box.w <= tile.x) {
		
		return false;
	}
	
	//left intersects right of tile
	if (collision_box.x >= tile.x + tile.w) {
		
		return false;
	}
	
	return true;
}


bool Player::touchesWall() {

	//using 2D array
	//get tile player is currently in
	int curr_tile_x = collision_box.x - (collision_box.x % 16);
	int curr_tile_y = collision_box.y - (collision_box.y % 16);

	//get positions of tiles surrounding player (10 tiles total each frame)
	int tile_above_left_x = curr_tile_x - 16;
	int tile_above_left_y = curr_tile_y - 16;

	int tile_above_x = curr_tile_x;
	int tile_above_y = curr_tile_y - 16;

	int tile_above_right_x = curr_tile_x + 16;
	int tile_above_right_y = curr_tile_y - 16;

	int tile_head_right_x = curr_tile_x + 16;
	int tile_head_right_y = curr_tile_y;

	int tile_feet_right_x = curr_tile_x + 16;
	int tile_feet_right_y = curr_tile_y + 16;

	int tile_lower_right_x = curr_tile_x + 16;
	int tile_lower_right_y = curr_tile_y + 32;

	int tile_below_x = curr_tile_x;
	int tile_below_y = curr_tile_y + 32;

	int tile_below_left_x = curr_tile_x - 16;
	int tile_below_left_y = curr_tile_y + 32;

	int tile_feet_left_x = curr_tile_x - 16;
	int tile_feet_left_y = curr_tile_y + 16;

	int tile_head_left_x = curr_tile_x - 16;
	int tile_head_left_y = curr_tile_y;

	//also need to get tiles that are currently intersecting player
	int tile_head_x = curr_tile_x;
	int tile_head_y = curr_tile_y;
	int tile_feet_x = curr_tile_x;
	int tile_feet_y = curr_tile_y + 16;;

	collision_tiles_x[0] = tile_above_left_x / 16;
	collision_tiles_y[0] = tile_above_left_y / 16;

	collision_tiles_x[1] = tile_above_x / 16;
	collision_tiles_y[1] = tile_above_y / 16;

	collision_tiles_x[2] = tile_above_right_x / 16;
	collision_tiles_y[2] = tile_above_right_y / 16;

	collision_tiles_x[3] = tile_head_right_x / 16;
	collision_tiles_y[3] = tile_head_right_y / 16;

	collision_tiles_x[4] = tile_feet_right_x / 16;
	collision_tiles_y[4] = tile_feet_right_y / 16;

	collision_tiles_x[5] = tile_lower_right_x / 16;
	collision_tiles_y[5] = tile_lower_right_y / 16;

	collision_tiles_x[6] = tile_below_x / 16;
	collision_tiles_y[6] = tile_below_y / 16;

	collision_tiles_x[7] = tile_below_left_x / 16;
	collision_tiles_y[7] = tile_below_left_y / 16;

	collision_tiles_x[8] = tile_feet_left_x / 16;
	collision_tiles_y[8] = tile_feet_left_y / 16;

	collision_tiles_x[9] = tile_head_left_x / 16;
	collision_tiles_y[9] = tile_head_left_y / 16;

	collision_tiles_x[10] = tile_head_x / 16;
	collision_tiles_y[10] = tile_head_y / 16;

	collision_tiles_x[11] = tile_feet_x / 16;
	collision_tiles_y[11] = tile_feet_y / 16;


	// for (int i = 0; i <= 11; i++) {

	// 	int row = collision_tiles_y[i];
	// 	int col = collision_tiles_x[i];

	// 	//set tiles that have collision
	// 	if((curr_map->get_tile_type(row, col) >= 0 && curr_map->get_tile_type(row, col) <= 4)) {
			
	// 		if (checkCollision(curr_map->get_collision_box(row, col))) {
				
	// 			return true;
	// 		}
	// 	}
	// }

	// return false;

	for (int i = 0; i < curr_map->getMapHeight(); i++) {

		for (int j = 0; j < curr_map->getMapWidth(); j++) {
		
			//set tiles that have collision
			if((curr_map->get_tile_type(i, j) >= 0 && curr_map->get_tile_type(i, j) <= 2)) {
				
				if (checkCollision(curr_map->get_collision_box(i, j))) {
					
					return true;
				}
			}
		}
	}

	return false;
}


bool Player::checkFloor(SDL_Rect tile) {

	if (feet.y + feet.h <= tile.y) { //collisionMap[i]

		return false;
	}
	
	//top intersects bottom of tile
	else if (feet.y >= tile.y + tile.h) {
		
		return false;
	}
	
	//right intersects left of tile
	else if (feet.x + feet.w <= tile.x) {
		
		return false;
	}
	
	//left intersects right of tile
	else if (feet.x >= tile.x + tile.w) {
		
		return false;
	}

	return true;
}


bool Player::touchesFloor() {
	
	//using 2D array
	//get tile player is currently in
	int curr_tile_x = feet.x - (feet.x % 16);
	int curr_tile_y = feet.y - (feet.y % 16);

	//get positions of tiles surrounding player (10 tiles total each frame)
	int tile_above_left_x = curr_tile_x - 16;
	int tile_above_left_y = curr_tile_y - 16;

	int tile_above_x = curr_tile_x;
	int tile_above_y = curr_tile_y - 16;

	int tile_above_right_x = curr_tile_x + 16;
	int tile_above_right_y = curr_tile_y - 16;

	int tile_feet_right_x = curr_tile_x + 16;
	int tile_feet_right_y = curr_tile_y;

	int tile_below_right_x = curr_tile_x + 16;
	int tile_below_right_y = curr_tile_y + 16;

	int tile_below_x = curr_tile_x;
	int tile_below_y = curr_tile_y + 16;

	int tile_below_left_x = curr_tile_x - 16;
	int tile_below_left_y = curr_tile_y + 16;

	int tile_feet_left_x = curr_tile_x - 16;
	int tile_feet_left_y = curr_tile_y;

	//also need to get tiles that are currently intersecting player's feet
	int tile_feet_x = curr_tile_x;
	int tile_feet_y = curr_tile_y;

	collision_tiles_x[0] = tile_above_left_x / 16;
	collision_tiles_y[0] = tile_above_left_y / 16;

	collision_tiles_x[1] = tile_above_x / 16;
	collision_tiles_y[1] = tile_above_y / 16;

	collision_tiles_x[2] = tile_above_right_x / 16;
	collision_tiles_y[2] = tile_above_right_y / 16;

	collision_tiles_x[3] = tile_feet_right_x / 16;
	collision_tiles_y[3] = tile_feet_right_y / 16;

	collision_tiles_x[4] = tile_below_right_x / 16;
	collision_tiles_y[4] = tile_below_right_y / 16;

	collision_tiles_x[5] = tile_below_x / 16;
	collision_tiles_y[5] = tile_below_y / 16;

	collision_tiles_x[6] = tile_below_left_x / 16;
	collision_tiles_y[6] = tile_below_left_y / 16;

	collision_tiles_x[7] = tile_feet_left_x / 16;
	collision_tiles_y[7] = tile_feet_left_y / 16;

	collision_tiles_x[8] = tile_feet_x / 16;
	collision_tiles_y[8] = tile_feet_y / 16;


	// for (int i = 0; i <= 8; i++) {

	// 	int row = collision_tiles_y[i];
	// 	int col = collision_tiles_x[i];

	// 	//set tiles that have collision
	// 	if((curr_map->get_tile_type(row, col) >= 0 && curr_map->get_tile_type(row, col) <= 4)) {
			
	// 		if (checkFloor(curr_map->get_collision_box(row, col))) {
				
	// 			return true;
	// 		}
	// 	}
	// }

	//return false;

	//using allocated 2D array
	for (int i = 0; i < curr_map->getMapHeight(); i++) {

		for (int j = 0; j < curr_map->getMapWidth(); j++) {

			//set tiles that have collision
			if((curr_map->get_tile_type(i, j) >= 0 && curr_map->get_tile_type(i, j) <= 2)) {
				
				if (checkFloor(curr_map->get_collision_box(i, j))) {
					
					return true;
				}
			}
		}
	}

	return false;
}


void Player::play_animations(float dT) {
	
	if (xVel != 0.0f && is_grounded) {
		
		//running right
		if (facing_right) {

			animation->setProperties(textureID, WALK, 4, 150);
		}
		
		//running left
		else {
			
			animation->setProperties(textureID, WALK, 4, 150, SDL_FLIP_HORIZONTAL);
		}
	}
	
	//jump
	if (yVel < 0.0f) {
		
		if (facing_right) {
			
			animation->setProperties(textureID, JUMP, 1, 100);
		}
		
		else {
			
			animation->setProperties(textureID, JUMP, 1, 100, SDL_FLIP_HORIZONTAL);
		}
	}
	
	//fall
	if (yVel > 0) {
		
		if (facing_right) {
			
			animation->setProperties(textureID, FALL, 1, 100);
		}
		
		else {
			
			animation->setProperties(textureID, FALL, 1, 100, SDL_FLIP_HORIZONTAL);
		}
	}

	if (Input::getInstance()->getKeyUp(SDL_SCANCODE_A) && Input::getInstance()->getKeyUp(SDL_SCANCODE_D) && is_grounded && xVel == 0.0f) {
		
		//Default Idle
		if (facing_right) {
			
			animation->setProperties(textureID, IDLE, 8, 200);
		}
		
		else {
			
			animation->setProperties(textureID, IDLE, 8, 200, SDL_FLIP_HORIZONTAL);
		}
	}
	
	if (is_crouching == true && is_grounded == true) {
		
		if (facing_right) {
			
			animation->setProperties(textureID, CRAWL, 4, 100);
		}
		
		else {
			
			animation->setProperties(textureID, CRAWL, 4, 100, SDL_FLIP_HORIZONTAL);
		}
	}
	
	//Attack
	if (Input::getInstance()->getKeyDown(SDL_SCANCODE_SPACE)) {
		
		if (facing_right) {
			
			animation->setProperties(textureID, ATTACK, 4, 100);
		}
		
		else {
			
			animation->setProperties(textureID, ATTACK, 4, 100, SDL_FLIP_HORIZONTAL);
		}
	}
}


void Player::move(float dT) {
	
	//move player--------------------------------
	if (adjustedY >= 290 || adjustedY <= -290) {
		
		xVel = 0.0f;
		yVel = 0.0f;

		xPos = xResetPos;
		yPos = yResetPos;

		facing_right = true;
	}
	
	//make player fall
	yVel += gravity * dT;

	if (yVel != 0.0f) {

		is_grounded = false;
		can_jump = false;
	}
	
	if (yVel >= terminal_yVel) {
		
		yVel = terminal_yVel;
	}

	//less gravity when jumping
	if (yVel < 0.0f) {

		gravity = jump_gravity;
	}

	if (is_falling) {
		
		gravity = fall_gravity;
	}
	
	//variable jump height
	if (xVel >= max_acceleration || xVel <= -max_acceleration) {

		jump_height = run_jump_height;
	}
	
	else {

		jump_height = walk_jump_height;
	}
	
	//stop player--------------------------------
	xPos += xVel * dT;
	collision_box.x = static_cast<int>(xPos + collision_offset_x);
	feet.x = static_cast<int>(xPos + collision_offset_x);
	
	if (touchesWall()) {
		
		//xPos -= xVel * dT;
		//collision_box.x = static_cast<int>(xPos + collision_offset_x);
		int snap_to = static_cast<int>(xPos) % 16;

		if (xVel >= 0.0f) {

			xPos = xPos - snap_to + 10;
			collision_box.x = static_cast<int>(xPos + collision_offset_x);
			feet.x = static_cast<int>(xPos + collision_offset_x);

			xVel = 0.0f;
		}
		
		if (xVel < 0.0f) {

			xPos = xPos + snap_to - 4;
			collision_box.x = static_cast<int>(xPos + collision_offset_x);
			feet.x = static_cast<int>(xPos + collision_offset_x);

			xVel = 0.0f;
		}
	}
	
	yPos += yVel * dT;
	collision_box.y = static_cast<int>(yPos + collision_offset_y);
	feet.y = static_cast<int>(yPos + height);

	if (touchesWall()) {

		//yPos -= yVel * dT;
		//collision_box.y = static_cast<int>(yPos + collision_offset_y);
		int snap_to = static_cast<int>(yPos) % 16;

		if (yVel > 0.0f) {

			yPos = yPos - snap_to;
			collision_box.y = static_cast<int>(yPos + collision_offset_y);
			feet.y = static_cast<int>(yPos + height);

			gravity = 0.0f;
		}

		//still up for debate, but not snapping here should prevent player from shooting downwards when clipped into a tile
		if (yVel < 0.0f) {
			
			// yPos -= yVel * dT;
			// collision_box.y = static_cast<int>(yPos + collision_offset_y);
			// feet.y = static_cast<int>(yPos + height - 1);

			yPos = yPos - collision_offset_y - snap_to + 16;
			collision_box.y = static_cast<int>(yPos + collision_offset_y);
			feet.y = static_cast<int>(yPos + height);
		}

		//the below if closely replicates Mario Bros. NES wall jumping exploit. (prevents player from glitching through walls when hitting corners)
		if (yVel == 0.0f) {

			//adding four prevents player from moving up 4 pixels when hitting wall at a corner angle... for some reason.
			yPos = yPos - collision_offset_y + 8;

			if (facing_right) {

				xPos = xPos - snap_to + 10;
				collision_box.x = static_cast<int>(xPos + collision_offset_x);
				feet.x = static_cast<int>(xPos + collision_offset_x);

				xVel = 0.0f;
			}

			else {

				xPos = xPos + snap_to + 4;
				collision_box.x = static_cast<int>(xPos + collision_offset_x);
				feet.x = static_cast<int>(xPos + collision_offset_x);

				xVel = 0.0f;
			}
		}

		yVel = 0.0f;

		//gravity = 0.0f;

		is_grounded = true;
		can_jump = true;
	}

	//let gravity pull player down if no tile is beneath
	if (touchesFloor()) {

		is_falling = false;
		//gravity = fall_gravity;
	}

	else {

		is_falling = true;
	}


	//SNAP CHARACTER TO CLOSEST 16TH GRID minus ONE???

	adjustedX = static_cast<int>(xPos);
	adjustedY = static_cast<int>(yPos);
	collision_box.x = adjustedX + collision_offset_x;
	collision_box.y = adjustedY + collision_offset_y;
	feet.x = adjustedX + collision_offset_x;
	feet.y = adjustedY + height;
}


void Player::control(float dT) {

	//adjusting player physics

	//get keyboard inputs if no controller is connected
	if (Engine::getInstance()->joystickConnected() == false) {

		//Run Left
		if (Input::getInstance()->getKeyDown(SDL_SCANCODE_A) && is_crouching == false) {
			
			facing_right = false;
			
			xVel -= acceleration * dT;

			if (xVel <= -max_acceleration) {
				
				xVel = -max_acceleration;

				//xVel += deceleration * dT;
			}
		}
		
		//key release left
		if (Input::getInstance()->getKeyUp(SDL_SCANCODE_A) && xVel <= 0.0f) {
			
			if (is_grounded) {
				
				xVel += deceleration * dT;
			}
			
			if (xVel >= 0.0f) {
				
				xVel = 0.0f;
			}
		}
		
		//Run Right
		if (Input::getInstance()->getKeyDown(SDL_SCANCODE_D) && is_crouching == false) {

			facing_right = true;
			
			xVel += acceleration * dT;
			
			if (xVel >= max_acceleration) {
				
				xVel = max_acceleration;

				//xVel -= deceleration * dT;
			}
		}
		
		//key release right
		if (Input::getInstance()->getKeyUp(SDL_SCANCODE_D) && xVel >= 0.0f) {

			if (is_grounded) {
				
				xVel -= deceleration * dT;
			}
			
			if (xVel <= 0) {
				
				xVel = 0;
			}
		}

		//press Left Shift
		if (Input::getInstance()->getKeyDown(SDL_SCANCODE_LSHIFT)) {

			
		}
		
		//release Left Shift
		if (Input::getInstance()->getKeyUp(SDL_SCANCODE_LSHIFT)) {

			
		}
		
		//press both left and right
		if (Input::getInstance()->getKeyDown(SDL_SCANCODE_A) && Input::getInstance()->getKeyDown(SDL_SCANCODE_D)) {
			
			if (is_grounded) {

				if (xVel <= 0) {
					
					xVel += deceleration * dT;
					
					if (xVel >= 0) {
						
						xVel = 0;
					}
				}
				
				if (xVel >= 0) {
					
					xVel -= deceleration * dT;
					
					if (xVel <= 0) {
						
						xVel = 0;
					}
				}
			}
		}

		//press both left and crouch
		if (Input::getInstance()->getKeyDown(SDL_SCANCODE_A) && Input::getInstance()->getKeyDown(SDL_SCANCODE_S)) {
			
			is_crouching = false;
		}


		//Jump
		if (Input::getInstance()->getKeyDown(SDL_SCANCODE_W)) {
			
			if (jump_button_released && is_grounded) {
				
				yVel -= jump_height;

				can_jump = false;

				is_jumping = true;
			}

			jump_button_released = false;
		}

		//key release jump
		if (Input::getInstance()->getKeyUp(SDL_SCANCODE_W)) {
			
			jump_button_released = true;

			if (is_jumping == true && yVel <= 0.0f) {

				yVel *= min_jump_height;
			}

			if (can_jump == false || is_grounded) {

				is_jumping = false;
			}
		}
		
		//Crouch
		if (Input::getInstance()->getKeyDown(SDL_SCANCODE_S)) {

			if (is_grounded) {

				is_crouching = true;

				if (xVel <= 0.0f) {
					
					xVel += deceleration * dT;
					
					if (xVel >= 0.0f) {
						
						xVel = 0.0f;
					}
				}
				
				if (xVel >= 0) {
					
					xVel -= deceleration * dT;
					
					if (xVel <= 0.0f) {
						
						xVel = 0.0f;
					}
				}
			}

			//can_jump = false;
		}
		
		//stand
		else if (Input::getInstance()->getKeyUp(SDL_SCANCODE_S)) {

			is_crouching = false;
		}
	}


	//use controller inputs------------------------------------------------------------------------------------------------
	else {
	
		//Run Left
		if (Input::getInstance()->getHatDown(SDL_HAT_LEFT)) {
			
			facing_right = false;
			
			xVel -= acceleration * dT;

			if (xVel <= -max_acceleration) {
				
				xVel = -max_acceleration;
			}
		}
		
		//key release left
		if (Input::getInstance()->getHatUp(SDL_HAT_LEFT) && xVel <= 0) {
			
			if (is_grounded) {
				
				xVel += deceleration * dT;
			}
			
			if (xVel >= 0.0f) {
				
				xVel = 0.0f;
			}
		}
		
		//Run Right
		if (Input::getInstance()->getHatDown(SDL_HAT_RIGHT)) {
			
			facing_right = true;
			
			xVel += acceleration * dT;
			
			if (xVel >= max_acceleration) {
				
				xVel = max_acceleration;
			}
		}
		
		//key release right
		if (Input::getInstance()->getHatUp(SDL_HAT_RIGHT) && xVel >= 0) {
			
			if (is_grounded) {
				
				xVel -= deceleration * dT;
			}
			
			if (xVel <= 0.0f) {
				
				xVel = 0.0f;
			}
		}

		//press button 3 (y)
		if (Input::getInstance()->getButtonDown(3)) {

			
		}
		
		//release button 3 (y)
		if (Input::getInstance()->getButtonUp(3)) {

			
		}
		
		//Jump
		if (Input::getInstance()->getButtonDown(2)) {
			
			if (jump_button_released && is_grounded) {
				
				yVel -= jump_height;

				can_jump = false;

				is_jumping = true;
			}

			jump_button_released = false;
		}
		
		//key release jump
		if (Input::getInstance()->getButtonUp(2)) {
			
			jump_button_released = true;

			if (is_jumping == true && yVel <= 0.0f) {

				yVel *= min_jump_height;
			}

			if (can_jump == false || is_grounded) {

				is_jumping = false;
			}
		}
		
		//Crouch
		if (Input::getInstance()->getHatDown(SDL_HAT_DOWN)) {

			if (is_grounded) {

				is_crouching = true;

				if (xVel <= 0.0f) {
					
					xVel += deceleration * dT;
					
					if (xVel >= 0.0f) {
						
						xVel = 0.0f;
					}
				}
				
				if (xVel >= 0) {
					
					xVel -= deceleration * dT;
					
					if (xVel <= 0.0f) {
						
						xVel = 0.0f;
					}
				}
			}

			//can_jump = false;
		}
		
		//stand
		else if (Input::getInstance()->getHatUp(SDL_HAT_DOWN)) {

			is_crouching = false;
		}
	}
}


void Player::updateCollision() {

	if (is_crouching == true) {

		// collision_offset_y = ((height - 1) / 2) * scale;

		// collision_box.h = ((height) / 2) * scale;
	}

	else {

		collision_offset_y = 0;

		collision_box.h = (height * scale);
	}
}


//Update all things player related (movement, animation)
void Player::update(float dT) {
	
	control(dT);
	
	move(dT);

	//setCollisionTiles();

	//updateCollision();
	//-------------------------------------------
	
	//animate
	play_animations(dT);
	animation->update(dT);
	
	//std::cout << "Vel: " << xVel << ", " << yVel << std::endl;
	//std::cout << "Is Jumping: " << is_jumping << std::endl;
	//std::cout << "Can jump: " << can_jump << std::endl;
	//std::cout << "Grounded: " << is_grounded << std::endl;
	//std::cout << "Falling: " << is_falling << std::endl;
	//std::cout << "Pos: " << adjustedX << ", " << adjustedY << std::endl;

	//std::cout << anim_speed << std::endl;

	//std::cout << "grav: " << gravity << " accel: " << acceleration << " decel: " << deceleration << " jump: " << jump_height << std::endl;
	
	//camera stuffs
	Camera::getInstance()->setPosition(adjustedX, adjustedY, width, height);
	
	Camera::getInstance()->update(dT);
}