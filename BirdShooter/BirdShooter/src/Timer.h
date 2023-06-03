#pragma once
#include <SDL.h>
#include <string>
#include <functional> // include this header for std::function

namespace mEngine
{
	class Timer
	{
	public:
		Timer();

		void start();
		void stop();
		void pause();
		void unpause();

		Uint32 getTicks();

		bool isStarted();
		bool isPaused();

		void setDurationInMins(Uint32 minutes);
		void setDurationInSecs(Uint32 seconds);

		void AddSeconds(Uint32 seconds);

		Uint32 getRemainingTime();
		Uint32 GetRemainingSeconds();

		std::string LogCountDown();

		// Additional methods for task execution
		void setTask(std::function<void()> task, Uint32 intervalSeconds);
		void Update();

	private:
		Uint32 mStartTicks;
		Uint32 mPausedTicks;
		bool mPaused;
		bool mStarted;
		Uint32 mDuration;

		// Additional task-related members
		std::function<void()> mTask;
		Uint32 mInterval;
		Uint32 mLastTaskTime;
	};
}