#ifndef DEATHEXPLOSION_H
#define DEATHEXPLOSION_H

#include "../graphics/TextureManager.h"
#include "../animation/Animation.h"


class DeathExplosion {
	
	private:

        std::string textureID;

		Animation* animation;

        int xPos;

        int yPos;

		int width;

		int height;
		
	public:
		
		DeathExplosion(std::string id, int x, int y);
		
		DeathExplosion();
		
		~DeathExplosion();

        void destroy();
		
		void draw();
		
		void update(float dT);
};

#endif