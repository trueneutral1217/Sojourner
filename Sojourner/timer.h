#ifndef TIMER_H
#define TIMER_H

#include "Texture.h"

const int SCREEN_FPS=60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

//The application time based timer
class timer
{
    public:
		//Initializes variables
		timer();

		//The various clock actions
		void start();
		void stop();
		void restart();//stop,start timer.
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//adds ticks to the timer
		void setTicks(Uint32 x);

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

    private:
		//The clock time when the timer started
		Uint32 startTicks;

		//The ticks stored when the timer was paused
		Uint32 pausedTicks;

		//The timer status
		bool paused;
		bool started;
};

#endif // TIMER_H
