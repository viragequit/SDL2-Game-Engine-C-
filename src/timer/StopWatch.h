#ifndef STOPWATCH_H
#define STOPWATCH_H


class StopWatch {

	private:

        int start_ticks;

        int paused_ticks;

        bool paused;

        bool started;

	public:

        StopWatch();

	~StopWatch();

        void start();

        void stop();

        void pause();

        void unpause();

        int getTicks();

        bool isStarted();

        bool isPaused();
};

#endif