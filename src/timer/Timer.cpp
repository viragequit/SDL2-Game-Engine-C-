#include "Timer.h"
#include "../SDL2/SDL.h"
#include <thread>


Timer* Timer::instance = NULL;

Timer::Timer() {

	framesPassed = 0;

	isCountingFrames = false;

	time = SDL_GetTicks();
}


Timer::~Timer() {
	
	
}


void Timer::tick() {
	
	int currentTime = SDL_GetTicks();

	deltaTime = (currentTime - time) * (FPS / 1000.0f);
	
	if (deltaTime > DELTA_TIME) {
		
		deltaTime = DELTA_TIME;
	}
	
	time = currentTime;
}


float Timer::getDeltaTime() {
	
	return deltaTime;
}