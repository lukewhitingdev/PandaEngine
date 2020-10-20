#include "GameTimer.h"
#include <d3d11.h>
#include <sstream>

PandaEngine::GameTimer::GameTimer()
{
	// Init
	SecondsPerCount = 0.0f;
	deltaTime = -1.0f;
	baseTime = 0;
	pausedTime = 0;
	previousTime = 0;
	currentTime = 0;
	timerStopped = false;
	stopTime = (__int64)0.0f;

	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	SecondsPerCount = 1.0 / (double)countsPerSec;
}


PandaEngine::GameTimer::~GameTimer()
{
}

float PandaEngine::GameTimer::getGameTime() const
{
	if (timerStopped) {
		return(float)(((stopTime - pausedTime) - baseTime) * SecondsPerCount);
	}
	else {
		return(float)(((currentTime - pausedTime) - baseTime) * SecondsPerCount);
	}
}

float PandaEngine::GameTimer::getDeltaTime() const
{
	return (float)deltaTime;
}

float PandaEngine::GameTimer::getFPS() const
{
	return fps;
}

void PandaEngine::GameTimer::ResetTimer()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)& currTime);

	baseTime = currTime;
	previousTime = currTime;
	stopTime = 0;
	timerStopped = false;
}

void PandaEngine::GameTimer::StartTimer()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)& startTime);

	// if we are resuming the timer from a stopped state
	if (timerStopped) {
		pausedTime += (startTime - stopTime);

		// Reset the previous time back to the start time since the previous time is now invalid
		previousTime = startTime;


		// We are no longer stopped so reset these
		stopTime = 0;
		timerStopped = false;
	}
}

void PandaEngine::GameTimer::StopTimer()
{
	// Check if we are already stopped
	if (!timerStopped) {
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)& currTime);

		// Save the time we stopped at and set the timer to stopped
		stopTime = currTime;
		timerStopped = true;
	}
}

void PandaEngine::GameTimer::Tick()
{
	// If the timer is stopped dont tick
	if (timerStopped) {
		deltaTime = 0.0f;
		return;
	}

	// Get the time in the current frame
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)& currTime);
	currentTime = currTime;

	// Get the time differences between frames (deltaTime)
	deltaTime = (currentTime - previousTime) * SecondsPerCount;

	// Reset previous time for next frame
	previousTime = currentTime;

	// Make sure we dont encounter any wierd results with the processor going into power save mode and turning into a tardis (negative time numbers)
	if (deltaTime < 0.0f) {
		deltaTime = 0.0f;
	}


}

void PandaEngine::GameTimer::CalculateFrameStats()
{
	static int frameCount = 0;
	static float timeElapsed = 0.0f;

	frameCount++;

	if ((getGameTime() - timeElapsed) >= 1.0f){
		fps = (float)frameCount;
		frameTime = 1000.0f / fps;

		frameCount = 0;
		timeElapsed += 1.0f;
	}
}
