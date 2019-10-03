#pragma once
class Timer
{
public:

	Timer();

	// Seconds
	float const GameTime();
	float const DeltaTime();

	void Reset();
	void Start();
	void Stop();
	// Runs every frame
	void Tick();

private:
	double mSecondsPerCount;
	double mDeltaTime;

	_int64 mBaseTime;
	_int64 mPausedTime;
	_int64 mStopTime;
	_int64 mPrevTime;
	_int64 mCurrTime;

	bool mStopped;
};

