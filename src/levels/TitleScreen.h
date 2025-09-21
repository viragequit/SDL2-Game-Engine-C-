#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "../menus/SelectArrow.h"
#include "../props/AffinePlane.h"
#include "../props/ParallaxLayer.h"
#include "../animation/Animation.h"
#include "../timer/StopWatch.h"

class TitleScreen {
	
	private:
		
		std::string textureID;
		
		Animation* animation;

		SelectArrow* arrow;
		
		AffinePlane* plane;

		float scale;

		bool draw_intro;

		bool show_presents;

		bool show_gap;

		bool show_gap_two;

		bool show_create;

		StopWatch stop_watch;

		float display_time;

		float gap_time;

		void playIntro(float dT);

		int alpha = 0;


		//selection logic
		bool has_started;

		bool start_game;

		bool exit_game;
		
	public:
		
		TitleScreen(float s = 1.0f);
		
		TitleScreen();
		
		~TitleScreen();
		
		void draw();
		
		void destroy();

		void control(float dT);

		bool getHasStarted();
		
		void update(float dT);
};

#endif
