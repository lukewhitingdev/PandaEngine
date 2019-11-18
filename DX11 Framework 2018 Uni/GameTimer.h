#pragma once
#include <d3d11_1.h>
class GameTimer
{
public:
	GameTimer();
	~GameTimer();

	float getGameTime()const; // Return the time in seconds
	float getDeltaTime()const; // Returns delta time in seconds

	void ResetTimer();
	void StartTimer();
	void StopTimer();
	void Tick();

	void CalculateFrameStats(HWND& hwnd);

private:
	double SecondsPerCount;
	double deltaTime;

	__int64 baseTime;
	__int64 pausedTime;
	__int64 stopTime;
	__int64 previousTime;
	__int64 currentTime;

	bool timerStopped;
};

