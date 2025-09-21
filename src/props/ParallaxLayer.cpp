#include "ParallaxLayer.h"
#include "../camera/Camera.h"
#include <iostream>


ParallaxLayer::ParallaxLayer(std::string id, float x, float y, float s, float scl) {
	
	textureID = id;
	
	xPos = x;
	
	yPos = y;
	
	speed = s;
	
	scale = scl;
}

ParallaxLayer::ParallaxLayer() {
	
	
}

ParallaxLayer::~ParallaxLayer() {
	
	
}

//THIS NEED TO BE FIXED AT SOME POINT TO ACTUALLY RESET THE TEXTURE INSTEAD OF REPEATING IT STATICALLY
void ParallaxLayer::draw() {
	
	//TextureManager::getInstance()->draw(textureID, (xPos - Camera::getInstance()->getXPos()) * speed, yPos - Camera::getInstance()->getYPos(), SDL_FLIP_NONE, scale);

	int width = TextureManager::getInstance()->getWidth(textureID);

	int height = TextureManager::getInstance()->getHeight(textureID);

	TextureManager::getInstance()->drawRepeat(textureID, (xPos - Camera::getInstance()->getXPos()) * speed, yPos - Camera::getInstance()->getYPos(), width, height, 0, 0, 1, 10, SDL_FLIP_NONE, scale);
}

void ParallaxLayer::update(float dT) {

	
}

void ParallaxLayer::setAlpha(int alpha) {

	TextureManager::getInstance()->setAlpha(textureID, alpha);
}