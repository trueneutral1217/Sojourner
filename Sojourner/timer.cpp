#include "timer.h"

timer::timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;

    paused = false;
    started = false;
}

void timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void timer::restart()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;

	//Clear tick variables
	startTicks = 0;
	pausedTicks = 0;
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;

	//Clear tick variables
	startTicks = 0;
	pausedTicks = 0;
}

void timer::pause()
{
    //If the timer is running and isn't already paused
    if( started && !paused )
    {
        //Pause the timer
        paused = true;
        std::cout<<"\n pause";
        std::cout<<"\n pausedTicks before operating = "<<pausedTicks;
        std::cout<<"\n SDL_GetTicks() before operating = "<<SDL_GetTicks();
        std::cout<<"\n startTicks before operating = "<<startTicks;
        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
        std::cout<<"\n pausedTicks after operating = "<<pausedTicks;
        std::cout<<"\n end pause function";
		startTicks = 0;
		//std::cout<<"\n pause: startTicks = 0, pausedTicks = "<<pausedTicks;
    }
}

void timer::unpause()
{
    //If the timer is !running and paused
    if( !started && paused )
    {
        //Unpause the timer
        paused = false;

        std::cout<<"\n unpause";
        std::cout<<"\n pausedTicks (before set to 0) = "<<pausedTicks;
        std::cout<<"\n startTicks (before operating) = "<<startTicks;
        std::cout<<"\n SDL_GetTicks() (before operating) = "<<SDL_GetTicks();
        //Reset the starting ticks
        //startTicks = SDL_GetTicks() - pausedTicks;


        startTicks = pausedTicks;

        std::cout<<"\n startTicks (after startTicks = pausedTicks) = "<<startTicks;
        std::cout<<"\n end unpause function";
        //Reset the paused ticks
        pausedTicks = 0;

        started = true;
    }
}

Uint32 timer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

    //If the timer is running
    if( started )
    {
        //If the timer is paused
        if( paused )
        {
            //Return the number of ticks when the timer was paused
            time = pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - startTicks;
        }
    }

    return time;
}
void timer::setTicks(Uint32 x)
{
	if(started)
    {
        startTicks += x;
    }

    if(paused)
    {
        pausedTicks += x;
    }

}

bool timer::isStarted()
{
	//Timer is running and paused or unpaused
    return started;
}

bool timer::isPaused()
{
	//Timer is running and paused
    return paused && started;
}

void timer::setPaused()
{
    paused = true;
    started = false;
}

void timer::updatePlayedTime()
{
    std::cout<<"\n running updatePlayedTime()";
    timePlayed += getTicks();
    std::cout<<"\n timePlayed = "<<timePlayed;
    pause();
}

void timer::restartPlayedTime()
{
    timePlayed=0;
    start();
}

void timer::loadSavedPlayedTimeData(Uint32 saved)
{
    std::cout<<"\n running loadSavedPlayedTimeData";
    std::cout<<"\n timePlayed before loading: "<<timePlayed;
    timePlayed=saved;
    std::cout<<"\n timePlayed after loading: "<<timePlayed;
    start();
}
