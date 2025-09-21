#ifndef AFFINEPLANE_H
#define AFFINEPLANE_H

#include "../graphics/TextureManager.h"

class AffinePlane {
	
	private:
		
		std::string textureID;

		SDL_Texture* new_texture = NULL;

		int sample_size;

        float fWorldX = 1000.0f;
		float fWorldY = 1000.0f;
		float fWorldA = 0.0f;

		float fNear = 0.01f;
		float fFar = 1.0f;
		float fFoVHalf = 3.14159f / 4.0f;
		
		int xPos;
		
		int yPos;

		int width;

		int height;
		
		float scale;

		int og_texture_width;

		int og_texture_height;

        void* pixels;

        int pitch;

		void applySineWave(Uint32* og_pixels, Uint32* txt_pixels, int width, int height, double time);

		void applyModeSeven(Uint32* og_pixels, Uint32* txt_pixels);
		
		double amplitude;
		double freq;
		double speed;
		double time;
		
	public:
		
		AffinePlane(std::string id, int samp_size, int x, int y, int w, int h, float scl = 1.0);
		
		AffinePlane();
		
		~AffinePlane();
		
		void draw();
		
		void update(float dT);

		void setAlpha(int alpha);
};

#endif