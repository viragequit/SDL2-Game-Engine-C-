#ifndef TESTLEVEL_H
#define TESTLEVEL_H

#include "../animation/Animation.h"
#include "../tilemap/Tilemap.h"
#include "../characters/Player.h"
#include "../enemies/BigEye.h"
#include "../items/GoldenAcorn.h"
#include "../props/ParallaxLayer.h"
#include "../props/AffinePlane.h"
#include "../effects/DeathExplosion.h"
#include "../timer/StopWatch.h"

class TestLevel {
	
	private:

		bool draw_level;

		StopWatch stop_watch;

		//objects
		Player* player = NULL;

		BigEye* bigeye = NULL;

		Tilemap* map = NULL;

		AffinePlane* mode_seven = NULL;

		ParallaxLayer* bg1 = NULL;
		ParallaxLayer* bg2 = NULL;
		ParallaxLayer* bg3 = NULL;

		DeathExplosion* death = NULL;


		void playIntro(float dT);
		
	public:
		
		TestLevel(bool show = false);
		
		TestLevel();
		
		~TestLevel();
		
		void draw();
		
		void destroy();

		void control(float dT);
		
		void update(float dT);
};

#endif
