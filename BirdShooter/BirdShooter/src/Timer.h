#pragma once
#include <SDL.h>
#include <string>

//The application time based timer
class Timer
{
public:
	//Initializes variables
	Timer();

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	Uint32 getTicks();

	//Checks the status of the timer
	bool isStarted();
	bool isPaused();

	// Sets the countdown duration
	void setDurationInMins(Uint32 minutes);
	void setDurationInSecs(Uint32 seconds);

	void AddSeconds(Uint32 seconds);

	// Gets the remaining time
	Uint32 getRemainingTime();

	Uint32 GetRemainingSeconds();

	std::string LogCountDown();

private:
	//The clock time when the timer started
	Uint32 mStartTicks;

	//The ticks stored when the timer was paused
	Uint32 mPausedTicks;

	//The timer status
	bool mPaused;
	bool mStarted;

	// The countdown duration
	Uint32 mDuration;
};

