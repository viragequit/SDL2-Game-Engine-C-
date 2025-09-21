#ifndef TILEMAP_H
#define TILEMAP_H

#include "../SDL2/SDL.h"
#include "../SDL2/SDL_image.h"
#include <string>


class Tilemap {
	
	private:
	
		std::string textureID;

		std::string map_file;
		
		int rows;
		
		int cols;
		
		int tile_width;
		
		int tile_height;
		
		int num_tiles;
		
		int scale;
		
		//make sure num_tiles and number of sprite clips are same
		//SDL_Rect spriteClips[7];

		SDL_Rect* spriteClips;
		
		//emplement dynamic array and read file data into it (typical size should be 12 rows by whatever number of columns for level length)
		//level length can be measured in screens with 20 tiles being one screen long
		
		//MUST AJUST IF TILE SIZE IS SMALLER OR BIGGER THAN 16Xx16
		int map_width = 192;
		int map_height = 14;

		int map[14][192];

		SDL_Rect collisionMap[14][192];

		void read_map();
		
	public:
		
		//textureID, map width (tiles), map height (tiles), tile width (pixels), tile height (pixels), number of tiles in tileset, scale
		Tilemap(std::string, std::string, int, int, int, int, int, int s = 1);
		
		Tilemap();
		
		~Tilemap();

		void destroy();
		
		void draw();
		
		int get_tile_type(int i, int j);
		
		SDL_Rect get_collision_box(int i, int j);

		int getMapWidth();

		int getMapHeight();
};

#endif
