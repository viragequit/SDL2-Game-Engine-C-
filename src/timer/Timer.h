#ifndef TIMER_H
#define TIMER_H


class Timer {

	private:
		
		//Initializes variables
		Timer();
		
		~Timer();
		
		static Timer* instance;
		
		float deltaTime;
		
		float time;

		int framesPassed;

		bool isCountingFrames;
		
	public:
		
		const int FPS = 60;
		
		const float DELTA_TIME = 1.5f;
		
		static Timer* getInstance() {
			
			if (!instance) {
				
				instance = new Timer();
			}
			
			return instance;
		}

		void tick();
		
		float getDeltaTime();
};

#endif