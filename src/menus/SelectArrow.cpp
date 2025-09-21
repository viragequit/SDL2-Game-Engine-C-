#include "SelectArrow.h"
#include "../engine/Engine.h"
#include "../graphics/TextureManager.h"
#include "../input/Input.h"
#include <iostream>


SelectArrow::SelectArrow(std::string id, int x, int y, int w, int h, int s) {
	
	animation = new Animation();
	
	textureID = id;

	xPos = x;
	
	yPos = y;
	
	width = w;
	
	height = h;
	
	scale = s;
	
	//animation->setProperties(textureID, RUN, 8, 100);
}

SelectArrow::SelectArrow() {
	
	
}


SelectArrow::~SelectArrow() {
	
	destroy();
}


void SelectArrow::draw() {
	
	//animation->draw((int)(xPos - camX), (int)(yPos - camY), width, height, scale);

	animation->draw(xPos, yPos, width, height, scale);
}


void SelectArrow::destroy() {
	
	std::cout << "Select Arrow deleted." << std::endl;
	
	delete animation;
}


void SelectArrow::play_animations() {
	
	animation->setProperties(textureID, CHOOSE, 6, 100);
}


void SelectArrow::setPosX(int x) {

	xPos = x;
}


void SelectArrow::setPosY(int y) {

	yPos = y;
}


//Update all things SelectArrow related (movement, animation)
void SelectArrow::update(float dT) {
	
	//animate
	play_animations();
	animation->update(dT);
}