#include "Debug.h"



Debug::Debug()
{
}

void Debug::DebugToOutput(std::string text)
{
	OutputDebugStringA(text.c_str());
}

void Debug::DebugToOutput(std::string precursor, int value)
{
	char sz[1024] = { 0 };
	sprintf_s(sz, "%s %d \n", precursor.c_str(), value);

	OutputDebugStringA(sz);
}

void Debug::DebugToOutput(int value)
{
	char sz[1024] = { 0 };
	sprintf_s(sz, "%d \n", value);
	OutputDebugStringA(sz);
}

void Debug::DebugToOutput(std::string precursor, float value)
{
	char sz[1024] = { 0 };
	sprintf_s(sz, "%s %f \n", precursor.c_str(), value);

	OutputDebugStringA(sz);
}

void Debug::DebugToOutput(float value)
{
	char sz[1024] = { 0 };
	sprintf_s(sz, "%f \n", value);
	OutputDebugStringA(sz);
}


Debug::~Debug()
{
}
