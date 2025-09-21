#ifndef PARALLAXLAYER_H
#define PARALLAXLAYER_H

#include "../graphics/TextureManager.h"

class ParallaxLayer {
	
	private:
		
		std::string textureID;
		
		float xPos;
		
		float yPos;
		
		float scale;
		
		float speed;
		
		
	public:
		
		ParallaxLayer(std::string id, float x, float y, float s, float scl = 1.0);
		
		ParallaxLayer();
		
		~ParallaxLayer();
		
		void draw();
		
		void update(float dT);

		void setAlpha(int alpha);
};

#endif