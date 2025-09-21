#include "BigEye.h"
#include "../engine/Engine.h"
#include "../graphics/TextureManager.h"
#include "../camera/Camera.h"
#include <iostream>
#include <cmath>


BigEye::BigEye(std::string id, int x, int y, int w, int h, int s) {
	
	animation = new Animation();
	
	textureID = id;
	
	xResetPos = x;

	yResetPos = y;

	xPos = x;
	
	yPos = y;

	center_x = xPos + 16;
	center_y = yPos + 16;

	adjustedX = x;

	adjustedY = y;
	
	width = w;
	
	height = h;
	
	scale = s;
	
	//physics variables-------------
	acceleration = 0.08f;
	
	deceleration = 0.16f;
	//-------------------------------
	
	collision_offset_x = 5;

	collision_offset_y = 5;

	collision_box.x = (adjustedX + collision_offset_x);

	collision_box.y = (adjustedY + collision_offset_y);
	
	collision_box.w = 22;
	
	collision_box.h = 22;
	
	facing_right = true;

	int mini_eye_x = 8;
	int mini_eye_y = 40;

	//mini eye stuff
	for (int i = 0; i < 8; i++) {;

		float angle = (static_cast<float>(i) / 8.0f) * 2.0f * M_PI;
    	mini_eye_array[i] = new MiniEye("minieye", center_x + cosf(angle) * orbitA, center_y + sinf(angle) * orbitB, 16, 16, 1);
    	mini_eye_array[i]->setAngle(angle); // set initial angle
	}
}

BigEye::BigEye() {
	
	
}


BigEye::~BigEye() {
	
	
}


void BigEye::draw() {
	
	//make sure in draw functions you account for camera offset!
	float camX = Camera::getInstance()->getXPos();
	
	float camY = Camera::getInstance()->getYPos();
	
	//animation->draw((int)(xPos - camX), (int)(yPos - camY), width, height, scale);

	animation->draw(static_cast<int>(xPos - camX), static_cast<int>(yPos - camY), width, height, scale);
	
	
	//for testing only
	collision_box.x -= static_cast<int>(camX);
	collision_box.y -= static_cast<int>(camY);

	for (int i = 0; i < 8; i++) {

		mini_eye_array[i]->draw();
	}
	
	//SDL_RenderDrawRect(Engine::getInstance()->getRenderer(), &collision_box);
}


void BigEye::destroy() {
	
	for (int i = 0; i < 8; i++) {

		delete mini_eye_array[i];
	}

	std::cout << "BigEye deleted." << std::endl;
	
	delete animation;
}


bool BigEye::checkCollision(SDL_Rect tile) {

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


void BigEye::play_animations(float dT) {
	
	animation->setProperties(textureID, TURN, 1, 150);
}


void BigEye::move(float dT) {
	
	//move BigEye--------------------------------
	if (adjustedY >= 290 || adjustedY <= -290) {
		
		xVel = 0.0f;
		yVel = 0.0f;

		xPos = xResetPos;
		yPos = yResetPos;

		facing_right = false;
	}

	center_x = (int)xPos + 16;
	center_y = (int)yPos + 16;
	

	//SNAP CHARACTER TO CLOSEST 16TH GRID minus ONE???

	adjustedX = static_cast<int>(xPos);
	adjustedY = static_cast<int>(yPos);
	collision_box.x = adjustedX + collision_offset_x;
	collision_box.y = adjustedY + collision_offset_y;
}


//Update all things BigEye related (movement, animation)
void BigEye::update(float dT) {
	
	move(dT);

	//setCollisionTiles();

	//updateCollision();
	//-------------------------------------------
	
	//animate
	play_animations(dT);
	animation->update(dT);

	for (int i = 0; i < 8; i++) {

		MiniEye* eye = mini_eye_array[i];
		float newAngle = eye->getAngle() - eye->getAcceleration() * dT; // angular velocity
		eye->setAngle(newAngle);

		float x = center_x + cosf(newAngle) * orbitA;
		float y = center_y + sinf(newAngle) * orbitB;

		eye->move(x, y, dT);
		eye->update(dT);
	}
}