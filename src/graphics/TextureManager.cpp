#include "TextureManager.h"
#include "../engine/Engine.h"
#include <iostream>


TextureManager* TextureManager::instance = NULL;


TextureManager::TextureManager() {
	
	
}


TextureManager::~TextureManager() {
	
	
}


bool TextureManager::load(std::string id, std::string filename) {
	
	SDL_Surface* image = IMG_Load(filename.c_str());
	
	if (image == NULL) {
		
		std::cout << "Failed to load texture: " << filename.c_str() << std::endl;
		
		std::cout << SDL_GetError() << std::endl;
		
		return false;
	}

	SDL_Surface* optimized = SDL_ConvertSurfaceFormat(image, SDL_GetWindowPixelFormat(Engine::getInstance()->getWindow()), NULL);
	
	if (optimized == NULL) {
		
		std::cout << "Failed to optimize surface: " << SDL_GetError() << std::endl;
		
		return false;
	}

	SDL_FreeSurface(image);
	
	SDL_SetColorKey(optimized, SDL_TRUE, SDL_MapRGB(optimized->format, 0, 255, 255));

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::getInstance()->getRenderer(), optimized);

	if (texture == NULL) {
		
		std::cout << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
		
		return false;
	}

	//Keep in case plans change (bool to specify if we want to keep the surface)
	SDL_FreeSurface(optimized);
	
	textureMap[id] = texture;

	return true;
}


bool TextureManager::loadStreaming(std::string id, std::string filename) {
	
	SDL_Surface* image = IMG_Load(filename.c_str());
	
	if (image == NULL) {
		
		std::cout << "Failed to load texture: " << filename.c_str() << std::endl;
		
		std::cout << SDL_GetError() << std::endl;
		
		return false;
	}

	SDL_Surface* optimized = SDL_ConvertSurfaceFormat(image, SDL_GetWindowPixelFormat(Engine::getInstance()->getWindow()), NULL);
	
	if (optimized == NULL) {
		
		std::cout << "Failed to optimize surface: " << SDL_GetError() << std::endl;
		
		return false;
	}

	SDL_FreeSurface(image);
	
	SDL_SetColorKey(optimized, SDL_TRUE, SDL_MapRGB(optimized->format, 0, 255, 255));

	//Uint32 pixel_format = SDL_PIXELFORMAT_RGBA32;
	Uint32 pixel_format = optimized->format->format;

	//std::cout << "Pixel Format: " << SDL_GetPixelFormatName(pixel_format) << std::endl;

	SDL_Texture* texture = SDL_CreateTexture(Engine::getInstance()->getRenderer(), pixel_format, SDL_TEXTUREACCESS_STREAMING, optimized->w, optimized->h);

	if (texture == NULL) {
		
		std::cout << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
		
		return false;
	}

	void* pixels;
	int pitch;

	if (SDL_LockTexture(texture, NULL, &pixels, &pitch) != 0) {
		
		std::cerr << "Failed to lock texture: " << SDL_GetError() << std::endl;

		return false;
	}

	SDL_memcpy(pixels, optimized->pixels, optimized->h * optimized->pitch);

	SDL_UnlockTexture(texture);

	SDL_FreeSurface(optimized);

	textureMap[id] = texture;

	return true;
}


SDL_Texture* TextureManager::getTexture(std::string id) {

	return textureMap[id];
}


int TextureManager::getWidth(std::string id) {
	
	SDL_QueryTexture(textureMap[id], NULL, NULL, &width, &height);
	
	return width;
}


int TextureManager::getHeight(std::string id) {
	
	SDL_QueryTexture(textureMap[id], NULL, NULL, &width, &height);
	
	return height;
}


//Load Text Blended (Wrapped)
bool TextureManager::loadText(std::string id, std::string filename, std::string text, int size, SDL_Color color, int wrap) {
	
	font = TTF_OpenFont(filename.c_str(), size);
	
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, wrap);
	
	if (textSurface == NULL) {
		
		std::cout << "Failed to render text surface: " << filename.c_str() << std::endl;
		
		std::cout << TTF_GetError() << std::endl;
		
		return false;
	}
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::getInstance()->getRenderer(), textSurface);
	
	if (texture == NULL) {
		
		std::cout << "Failed to create texture from rendered text: " << SDL_GetError() << std::endl;
		
		return false;
	}
	
	else {
		
		width = textSurface->w;
        	height = textSurface->h;
	}
	
	SDL_FreeSurface(textSurface);
	
	textureMap[id] = texture;
	
	return true;
}


void TextureManager::remove(std::string id) {
	
	SDL_DestroyTexture(textureMap[id]);
	
	textureMap.erase(id);
}


void TextureManager::destroy() {
	
	std::map<std::string, SDL_Texture*>::iterator iter;
	
	//textureMap
	for (iter = textureMap.begin(); iter != textureMap.end(); iter++) {
		
		SDL_DestroyTexture(iter->second);
		
		//std::cout << "Texture \"" << iter->first << "\" destroyed!" << std::endl;
	}
	
	textureMap.clear();
	
	std::cout << "Texture map deleted." << std::endl;
}


void TextureManager::draw(std::string id, int x, int y, SDL_RendererFlip flip, float scale, float angle) {
	
	SDL_QueryTexture(textureMap[id], NULL, NULL, &width, &height);
	
	SDL_Rect sourceRect = {0, 0, width, height};
	
	SDL_Rect destinationRect = {(int)x, (int)y, width * scale, height * scale};
	
	SDL_RenderCopyEx(Engine::getInstance()->getRenderer(), textureMap[id], &sourceRect, &destinationRect, angle, NULL, flip);
}


void TextureManager::drawRepeat(std::string id, int x, int y, int width, int height, int s_row, int frame, int row, int col, SDL_RendererFlip flip, int scale) {
	
	SDL_Rect repeat[row][col];
	
	SDL_Rect sourceRect = {width * frame, height * s_row, width, height};
	
	SDL_Rect destinationRect = {x, y, width * scale, height * scale};
	
	for (int i = 0; i < row; ++i) {
		
		for (int j = 0; j < col; ++j) {
			
			SDL_RenderCopyEx(Engine::getInstance()->getRenderer(), textureMap[id], &sourceRect, &destinationRect, 0, NULL, flip);
			
			//destinationRect.x += width;
			destinationRect.x += width;
		}
		
		destinationRect.y += height;
		
		destinationRect.x = x;
	}
}


void TextureManager::drawText(std::string id, int x, int y, SDL_RendererFlip flip) {
	
	SDL_QueryTexture(textureMap[id], NULL, NULL, &width, &height);
	
	SDL_Rect sourceRect = {0, 0, width, height};
	
	SDL_Rect destinationRect = {x, y, width, height};
	
	SDL_RenderCopyEx(Engine::getInstance()->getRenderer(), textureMap[id], &sourceRect, &destinationRect, 0, NULL, flip);
}


void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip, int scale) {
	
	SDL_Rect sourceRect = {width * frame, height * row, width, height};
	
	SDL_Rect destinationRect = {x, y, width * scale, height * scale};
	
	SDL_RenderCopyEx(Engine::getInstance()->getRenderer(), textureMap[id], &sourceRect, &destinationRect, 0, NULL, flip);
}


void TextureManager::drawTile(std::string id, int x, int y, int w, int h, SDL_Rect* clip, int scale) {
	
	SDL_Rect renderQuad = {x, y, w, h};
	
	if (clip != NULL) {
		
		renderQuad.w = clip->w * scale;
		renderQuad.h = clip->h * scale;
	}
	
	SDL_RenderCopy(Engine::getInstance()->getRenderer(), textureMap[id], clip, &renderQuad);
}


void TextureManager::setAlpha(std::string id, Uint8 alpha) {
	
	SDL_SetTextureAlphaMod(textureMap[id], alpha);
}