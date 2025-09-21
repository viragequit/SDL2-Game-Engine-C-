#include "GoldenAcorn.h"
#include "../engine/Engine.h"
#include "../graphics/TextureManager.h"
#include "../camera/Camera.h"
#include <iostream>


GoldenAcorn::GoldenAcorn(std::string id, int x, int y, int w, int h, int scale) {

    textureID = id;

    animation = new Animation();

    xPos = x + 4;

    yPos = y;

    width = w;

    height = h;

    scl = scale;

	collision_box.x = xPos;

    collision_box.y = yPos;

    collision_box.w = 8;

    collision_box.h = 8;
}

GoldenAcorn::GoldenAcorn() {
	
	
}


GoldenAcorn::~GoldenAcorn() {
	
	
}


void GoldenAcorn::draw() {

    float camX = Camera::getInstance()->getXPos();
	
	float camY = Camera::getInstance()->getYPos();

	animation->draw((int)(xPos - camX), (int)(yPos - camY), width, height, scl);

    //animation->draw(xPos, yPos, width, height, scl);
}


void GoldenAcorn::destroy() {

	std::cout << "Acorn deleted." << std::endl;

    delete animation;
}


//Update all things GoldenAcorn related (movement, animation)
void GoldenAcorn::update(float dT) {

	animation->setProperties(textureID, 0, 4, 180);

    animation->update(dT);
}