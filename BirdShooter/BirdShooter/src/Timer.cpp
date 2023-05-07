#include "Timer.h"
#include <iostream>
#include <sstream>
#include <iomanip> // include this header to use std::setw

Timer::Timer()
{
	mStartTicks = 0;
	mPausedTicks = 0;
	mPaused = false;
	mStarted = false;
	mDuration = 0;
}

void Timer::start()
{
	//Start the timer
	mStarted = true;

	//Unpause the timer
	mPaused = false;

	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void Timer::stop()
{
	//Stop the timer
	mStarted = false;

	//Unpause the timer
	mPaused = false;

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void Timer::pause()
{
	//If the timer is running and isn't already paused
	if (mStarted && !mPaused)
	{
		//Pause the timer
		mPaused = true;

		//Calculate the paused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void Timer::unpause()
{
	//If the timer is running and paused
	if (mStarted && mPaused)
	{
		//Unpause the timer
		mPaused = false;

		//Reset the starting ticks
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		//Reset the paused ticks
		mPausedTicks = 0;
	}
}

Uint32 Timer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;
	//If the timer is running
	if (mStarted)
	{
		//If the timer is paused
		if (mPaused)
		{
			//Return the number of ticks when the timer was paused
			time = mPausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}
	}
	return time;
}

bool Timer::isStarted()
{
	//Timer is running and paused or unpaused
	return mStarted;
}

bool Timer::isPaused()
{
	//Timer is running and paused
	return mPaused && mStarted;
}

void Timer::setDurationInMins(Uint32 minutes)
{
	mDuration = minutes * 60 * 1001;
}

void Timer::setDurationInSecs(Uint32 seconds)
{
	mDuration = seconds * 1001;
}

void Timer::AddSeconds(Uint32 seconds)
{
	mDuration += (seconds * 1000);
}

Uint32 Timer::getRemainingTime()
{
	Uint32 time = 0;
	if (mStarted)
	{
		if (mPaused)
		{
			time = mDuration - mPausedTicks;
		}
		else
		{
			Uint32 currentTicks = SDL_GetTicks();
			Uint32 elapsedTicks = currentTicks - mStartTicks;
			if (elapsedTicks >= mDuration)
			{
				time = 0;
			}
			else
			{
				time = mDuration - elapsedTicks;
			}
		}
	}
	return time;
}

Uint32 Timer::GetRemainingSeconds()
{
	return getRemainingTime() / 1000;
}

std::string Timer::LogCountDown()
{
	// Get the remaining time in seconds
	int remainingTime = (getRemainingTime() / 1000);

	// Format the remaining time as a string
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(2) << (remainingTime / 60) << ":"
		<< std::setfill('0') << std::setw(2) << (remainingTime % 60);

	return ss.str();
}