#include "Timer.h"
#include <Windows.h>

Timer::Timer()
{

	// Init
	mSecondsPerCount = 0.0;
	mDeltaTime = -1.0;
	mBaseTime = 0;
	mPausedTime = 0;
	mPrevTime = 0;
	mCurrTime = 0;
	mStopped = false;

	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;

}

float const Timer::GameTime()
{
	if (mStopped) {
		// If stopped then return the paused time subtracted from the stopped time to get accurate time
		return (float)(((mStopTime - mPausedTime) - mBaseTime) * mSecondsPerCount);
	}
	else {
		// If we aint stopped then return current time without the paused time
		return (float)(((mCurrTime - mPausedTime) - mBaseTime)* mSecondsPerCount);
	}
}

float const Timer::DeltaTime()
{
	return (float)mDeltaTime;
}

void Timer::Reset()
{
	_int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

void Timer::Start()
{
	_int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	if (mStopped) {
		// If we are comming out a stop, then get the total paused time elapsed
		mPausedTime += (startTime - mStopTime);

		// Since the timer has been paused no other time var is valid
		mPrevTime = startTime;

		mStopTime = 0;
		mStopped = false;
	}
}


void Timer::Stop()
{
	/*
	* When we want to stop, if not already stopped then get the currentTime and save it for future use, then stop the time
	*/
	if (!mStopped) {
		_int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		mStopTime = currTime;
		mStopped = true;
	}
}

void Timer::Tick()
{
	if (mStopped) {
		mDeltaTime = 0.0;
		return;
	}

	// Get Time this frame
	_int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mCurrTime = currTime;

	// Get the time difference between frames
	mDeltaTime = (mCurrTime - mPrevTime) * mSecondsPerCount;

	// Prepare for the next frame coming
	mPrevTime = mCurrTime;

	// If the deltaTime is negative, the timer has been shuffled to another cpu or
	// its using powersaving mode, either way we dont want it.
	if (mDeltaTime < 0.0) {
		mDeltaTime = 0.0;
	}

}
