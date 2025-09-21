#include "MiniEye.h"
#include "../engine/Engine.h"
#include "../graphics/TextureManager.h"
#include "../camera/Camera.h"
#include <iostream>
#include <cmath>


MiniEye::MiniEye(std::string id, int x, int y, int w, int h, int s) {
	
	animation = new Animation();
	
	textureID = id;

	xPos = x;
	
	yPos = y;

	adjustedX = x;

	adjustedY = y;
	
	width = w;
	
	height = h;
	
	scale = s;
	
	//physics variables-------------
	acceleration = 0.06f;
	
	deceleration = 0.16f;
	//-------------------------------
	
	collision_offset_x = 4;

	collision_offset_y = 4;

	collision_box.x = (adjustedX + collision_offset_x);

	collision_box.y = (adjustedY + collision_offset_y);
	
	collision_box.w = 8;
	
	collision_box.h = 8;
	
	facing_right = true;
}

MiniEye::MiniEye() {
	
	
}


MiniEye::~MiniEye() {
	
	
}


void MiniEye::setAngle(float a) {

	angle = a;
};


float MiniEye::getAngle() {

	return angle;
};


void MiniEye::setAcceleration(float s) {

	acceleration = s;
}

float MiniEye::getAcceleration() {

	return acceleration;
};


void MiniEye::draw() {
	
	//make sure in draw functions you account for camera offset!
	float camX = Camera::getInstance()->getXPos();
	
	float camY = Camera::getInstance()->getYPos();
	
	//animation->draw((int)(xPos - camX), (int)(yPos - camY), width, height, scale);

	animation->draw(static_cast<int>(adjustedX - camX), static_cast<int>(adjustedY - camY), width, height, scale);
	
	
	//for testing only
	collision_box.x -= static_cast<int>(camX);
	collision_box.y -= static_cast<int>(camY);
	
	//SDL_RenderDrawRect(Engine::getInstance()->getRenderer(), &collision_box);
}


void MiniEye::destroy() {
	
	std::cout << "MiniEye deleted." << std::endl;
	
	delete animation;
}


bool MiniEye::checkCollision(SDL_Rect tile) {

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


void MiniEye::play_animations(float dT) {
	
	animation->setProperties(textureID, FLY, 2, 70);
}


void MiniEye::move(float x, float y, float dT) {

	xPos = x;
	yPos = y;

	adjustedX = static_cast<int>(xPos);
	adjustedY = static_cast<int>(yPos);
	collision_box.x = adjustedX + collision_offset_x;
	collision_box.y = adjustedY + collision_offset_y;
}


//Update all things MiniEye related (movement, animation)
void MiniEye::update(float dT) {

	//setCollisionTiles();

	//updateCollision();
	//-------------------------------------------
	
	//animate
	play_animations(dT);
	animation->update(dT);
}