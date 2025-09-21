#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "../SDL2/SDL.h"
#include "../SDL2/SDL_image.h"
#include "../SDL2/SDL_ttf.h"
#include <string>
#include <map>
#include <cmath>


class TextureManager {
	
	private:
		
		static TextureManager* instance;
		
		TextureManager();
		
		~TextureManager();
		
		std::map<std::string, SDL_Texture*> textureMap;
		
		int width;
		
		int height;
		
	public:
		
		static TextureManager* getInstance() {
			
			if (instance == NULL) {
				
				instance = new TextureManager();
			}
			
			return instance;
		}
		
		bool load(std::string, std::string);

		bool loadStreaming(std::string, std::string);
		
		SDL_Texture* getTexture(std::string id);
		
		int getWidth(std::string);
		
		int getHeight(std::string);
		
		bool loadText(std::string, std::string, std::string, int, SDL_Color, int wrap);
		
		TTF_Font* font;
		
		void remove(std::string);
		
		void destroy();
		
		void draw(std::string, int, int, SDL_RendererFlip flip = SDL_FLIP_NONE, float scale = 1.0f, float angle = 0.0f);
		
		void drawRepeat(std::string, int, int, int width, int height, int s_row, int frame, int row, int col, SDL_RendererFlip flip = SDL_FLIP_NONE, int scale = 1);
		
		void drawText(std::string, int, int, SDL_RendererFlip flip = SDL_FLIP_NONE);
		
		void drawFrame(std::string, int, int, int, int, int, int, SDL_RendererFlip flip = SDL_FLIP_NONE, int scale = 1);
		
		void drawTile(std::string, int, int, int, int, SDL_Rect*, int);
		
		void setAlpha(std::string, Uint8);

		void renderMode7(std::string id, float angle, int scale);
};

#endif