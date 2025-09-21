#include "Camera.h"
#include <iostream>


Camera* Camera::instance = NULL;


Camera::Camera() {
	
	
}


Camera::~Camera() {
	
	
}


int Camera::getWidth() {
	
	return width;
}


int Camera::getHeight() {
	
	return height;
}


int Camera::getXPos() {
	
	return xPos;
}


int Camera::getYPos() {
	
	return yPos;
}


void Camera::setPosition(int x, int y, int w, int h) {
	
	camera.x = (x + w / 2) - (width / 2);
	
	//no need to calculate camera.y for side scrolling levels. May need to change if we want free roaming levels like in Metroid
	//camera.y = (y + h / 2) - (height / 2);
}

void Camera::setBounds(int x_min, int x_max, int y_min, int y_max) {
	
	xMin = x_min;
	
	xMax = x_max;
	
	yMin = y_min;
	
	yMax = y_max;
}

void Camera::update(float dT) {
	
	xPos = camera.x;
	
	yPos = camera.y;
	
	//stop camera from moving past left of level
	if (xPos <= xMin) {
		
		xPos = xMin;
	}
	
	//stop camera from moving past right of level (level width - camera width) in the future
	if (xPos >= xMax) {
		
		xPos = xMax;
	}
	
	//for debugging purposes
	//std::cout << "Camera: " << xPos << " " << yPos << std::endl;
}
