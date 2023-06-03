
#include "Timer.h"
#include <iostream>
#include <sstream>
#include <iomanip> // include this header to use std::setw

namespace mEngine
{
	Timer::Timer()
	{
		mStartTicks = 0;
		mPausedTicks = 0;
		mPaused = false;
		mStarted = false;
		mDuration = 0;
		mTask = nullptr;
		mInterval = 0;
		mLastTaskTime = 0;
	}

	void Timer::start()
	{
		mStarted = true;
		mPaused = false;
		mStartTicks = SDL_GetTicks();
		mPausedTicks = 0;
	}

	void Timer::stop()
	{
		mStarted = false;
		mPaused = false;
		mStartTicks = 0;
		mPausedTicks = 0;
		mTask = nullptr;
		mInterval = 0;
		mLastTaskTime = 0;
	}

	void Timer::pause()
	{
		if (mStarted && !mPaused)
		{
			mPaused = true;
			mPausedTicks = SDL_GetTicks() - mStartTicks;
			mStartTicks = 0;
		}
	}

	void Timer::unpause()
	{
		if (mStarted && mPaused)
		{
			mPaused = false;
			mStartTicks = SDL_GetTicks() - mPausedTicks;
			mPausedTicks = 0;
		}
	}

	Uint32 Timer::getTicks()
	{
		Uint32 time = 0;
		if (mStarted)
		{
			if (mPaused)
			{
				time = mPausedTicks;
			}
			else
			{
				time = SDL_GetTicks() - mStartTicks;
			}
		}
		return time;
	}

	bool Timer::isStarted()
	{
		return mStarted;
	}

	bool Timer::isPaused()
	{
		return mPaused && mStarted;
	}

	void Timer::setDurationInMins(Uint32 minutes)
	{
		mDuration = minutes * 60 * 1000;
	}

	void Timer::setDurationInSecs(Uint32 seconds)
	{
		mDuration = seconds * 1000;
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
		int remainingTime = (getRemainingTime() / 1000);
		std::stringstream ss;
		ss << std::setfill('0') << std::setw(2) << (remainingTime / 60) << ":"
			<< std::setfill('0') << std::setw(2) << (remainingTime % 60);
		return ss.str();
	}

	void Timer::setTask(std::function<void()> task, Uint32 intervalSeconds)
	{
		mTask = task;
		mInterval = intervalSeconds * 1000;
		mLastTaskTime = 0;
	}

	void Timer::Update()
	{
		if (mTask && isStarted())
		{
			Uint32 currentTicks = SDL_GetTicks();
			Uint32 elapsedTicks = currentTicks - mStartTicks;

			if (elapsedTicks >= mLastTaskTime + mInterval)
			{
				mTask();
				mLastTaskTime = elapsedTicks;
			}
		}
	}
}