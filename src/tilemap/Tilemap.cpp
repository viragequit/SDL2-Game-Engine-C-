#include <fstream>
#include <sstream>
#include "Tilemap.h"
#include "../graphics/TextureManager.h"
#include "../camera/Camera.h"
#include <iostream>


Tilemap::Tilemap(std::string id, std::string file_path, int map_w, int map_h, int tile_w, int tile_h, int n_tiles, int s) {
	
	textureID = id;

	map_file = file_path;
	
	cols = map_w;
	
	rows = map_h;
	
	tile_width = tile_w;
	
	tile_height = tile_h;
	
	num_tiles = n_tiles;
	
	scale = s;

	read_map();

	spriteClips = new SDL_Rect[num_tiles];
	
	
	int x = 0;
	int y = 0;

	//allocate array for sprite clips (individual tiles)
	//spriteClips = new SDL_Rect[num_tiles];
	
	
	//use numTiles here in the future
	for (int i = 0; i < num_tiles; i++) {
		
		spriteClips[i].x = x;
		spriteClips[i].y = y;
		spriteClips[i].w = tile_width;
		spriteClips[i].h = tile_height;
		
		x += tile_width;
	}
	
	x = 0;
	y = 0;
	
	// for (int i = 0; i < rows * cols; i++) {
		
	// 	SDL_Rect collision_box;
		
	// 	collision_box.x = x;
		
	// 	collision_box.y = y;
		
	// 	collision_box.w = tile_width * scale;
		
	// 	collision_box.h = tile_width * scale;
		
	// 	collisionMap[i] = collision_box;
		
	// 	//std::cout << x << ", " << y << std::endl;
		
	// 	x += tile_width * scale;
		
	// 	if (x == cols * tile_width * scale) {
			
	// 		y += tile_height * scale;
			
	// 		x = 0;
	// 	}
	// }

	//uncomment when ready to use dynamically allocated 2D collision map array
	for (int i = 0; i < rows; i++) {

		for (int j = 0; j < cols; j++) {
			
			SDL_Rect collision_box;
			
			collision_box.x = x;
			
			collision_box.y = y;
			
			collision_box.w = tile_width * scale;
			
			collision_box.h = tile_width * scale;
			
			collisionMap[i][j] = collision_box;
			
			//std::cout << x << ", " << y << std::endl;
			
			x += tile_width * scale;
			
			if (x == cols * tile_width * scale) {
				
				y += tile_height * scale;
				
				x = 0;
			}
		}
	}
}

Tilemap::Tilemap() {
	
	
}

Tilemap::~Tilemap() {
	
	destroy();
}

void Tilemap::destroy() {

	delete spriteClips;
}

void Tilemap::read_map() {

	//int map_data[cols * rows];

	std::ifstream file(map_file);

	if (!file.is_open()) {

		std::cout << "Error opening file: " << map_file << std::endl;
	}

	std::string line;

	// int count = 0;

	// while (getline(file, line) && count < (cols * rows)) {

	// 	std::istringstream iss(line);
	// 	std::string value;

	// 	while (getline(iss, value, ',')) {

	// 		map[count] = std::stoi(value);

	// 		count++;
	// 	}
	// }

	//loading into dynamically allocated 2D array!
	int i = 0;
	while (getline(file, line) && i < rows) {

		std::istringstream iss(line);
		std::string value;

		int j = 0;

		while (getline(iss, value, ',') && j < cols) {

			map[i][j] = std::stoi(value);

			j++;
		}

		i++;
	}

	file.close();
}

void Tilemap::draw() {
	
	//vars used for old method drawing entire map
	//int x = 0;
	//int y = 0;

	
	int camX = Camera::getInstance()->getXPos();
	int camY = Camera::getInstance()->getYPos();
	int camW = Camera::getInstance()->getWidth();
	int camH = Camera::getInstance()->getHeight();

	// figure out tile range in indices (not pixels)
	int startCol = camX / tile_width;
	int startRow = camY / tile_height;
	int endCol   = (camX + camW) / tile_width;
	int endRow   = (camY + camH) / tile_height;

	// clamp to map size
	if (startCol < 0) startCol = 0;
	if (startRow < 0) startRow = 0;
	if (endCol >= cols) endCol = cols - 1;
	if (endRow >= rows) endRow = rows - 1;


	//use dynamically allocated 2D array instead
	// !!!! FIX THIS SO ONLY TILES WITHIN THE CAMERA VIEW ARE DRAWN !!!!
	// for (int i = 0; i < rows; i++) {

	// 	for (int j = 0; j < cols; j++) {
		
	// 		//draw tile map relative to camera offset
	// 		TextureManager::getInstance()->drawTile(textureID, x - Camera::getInstance()->getXPos(), y - Camera::getInstance()->getYPos(), tile_width, tile_height, &spriteClips[map[i][j]], scale);
			
	// 		x += tile_width * scale;
			
	// 		//shift down to next row
	// 		if (x == cols * tile_width * scale) {
				
	// 			y += tile_height * scale;
				
	// 			x = 0;
	// 		}
	// 	}
	// }

	for (int j = startRow; j <= endRow; j++) {

    	for (int i = startCol; i <= endCol; i++) {

        	int screenX = i * tile_width - camX;
        	int screenY = j * tile_height - camY;
			
			//draw tile map relative to camera offset
			TextureManager::getInstance()->drawTile(textureID, screenX, screenY, tile_width, tile_height, &spriteClips[map[j][i]], scale);
		}
	}
}

int Tilemap::get_tile_type(int i, int j) {
	
	//return map[i];

	//edit to get i, j values for 2D array cell
	if (i >= 0 && i <= map_height && j >= 0 && j <= map_width) {

		return map[i][j];
	}

	else {

		//std::cout << "out of bounds in tile map array!!!" << std::endl;

		return map[0][0];
	}
}

SDL_Rect Tilemap::get_collision_box(int i, int j) {
	
	//return collisionMap[i];

	//edit to get i,j values for 2D array cell
	if (i >= 0 && i < map_height && j >= 0 && j < map_width) {
		
		return collisionMap[i][j];
	}

	else {

		//std::cout << "out of bounds in collision map array!!!" << std::endl;

		return collisionMap[0][0];
	}
}

int Tilemap::getMapWidth() {

	return map_width;
}

int Tilemap::getMapHeight() {

	return map_height;
}