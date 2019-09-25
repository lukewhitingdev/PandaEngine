#include "input.h"



input::input()
{
}


input::~input()
{
}

void input::Init()
{
	// init all the keys to be released at the start
	for (int i = 0; i < 256; i++) {
		mKeys[i] = false;
	}

	return;
}

void input::KeyDown(unsigned int key)
{
	mKeys[key] = true;
	return;
}

void input::KeyUp(unsigned int key)
{
	mKeys[key] = false;
	return;
}

bool input::IsKeyDown(unsigned int key)
{
	return mKeys[key];
}
