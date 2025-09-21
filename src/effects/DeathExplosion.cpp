#include "DeathExplosion.h"
#include "../graphics/TextureManager.h"
#include "../camera/Camera.h"


DeathExplosion::DeathExplosion(std::string id, int x, int y) {

    textureID = id;

    animation = new Animation();

    animation->setProperties(textureID, 0, 9, 80);

    width = 64;

    height = 64;

    xPos = x;

    yPos = y;
}

DeathExplosion::DeathExplosion() {


}

DeathExplosion::~DeathExplosion() {


}

void DeathExplosion::destroy() {


}

void DeathExplosion::draw() {

    float camX = Camera::getInstance()->getXPos();
	float camY = Camera::getInstance()->getYPos();

    animation->draw(static_cast<int>(xPos - camX), static_cast<int>(yPos - camY), width, height);
}

void DeathExplosion::update(float dT) {

	animation->update(dT);
}