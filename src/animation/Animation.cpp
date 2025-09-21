#include "Animation.h"
#include "../graphics/TextureManager.h"
#include <iostream>


Animation::Animation() {
	
	sprite_frame = 0;
}


Animation::~Animation() {
	
	
}


void Animation::setProperties(std::string id, int row, int f_count, int anim_speed, SDL_RendererFlip flip) {
	
	textureID = id;
	
	sprite_row = row;

	sprite_frame = 0;
	
	frame_count = f_count;
	
	animation_speed = anim_speed;
	
	sprite_flip = flip;
}


void Animation::draw(int x, int y, int width, int height, int scale) {
	
	TextureManager::getInstance()->drawFrame(textureID, x, y, width, height, sprite_row, sprite_frame, sprite_flip, scale);
}


// void Animation::drawRepeat(int x, int y, int row, int col, float scale) {
	
// 	TextureManager::getInstance()->drawRepeat(textureID, x, y, width, height, sprite_row, sprite_frame, row, col, sprite_flip, scale);
// }


void Animation::update(float dT) {
	
	sprite_frame = (SDL_GetTicks() / animation_speed) % frame_count;

	//std::cout << sprite_frame << std::endl;
}
