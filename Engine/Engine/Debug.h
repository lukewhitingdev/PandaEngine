#pragma once
#include <string>
#include <Windows.h>

class Debug
{
public:
	Debug();
	static void DebugToOutput(std::string text);
	static void DebugToOutput(std::string precursor, int value);
	static void DebugToOutput(int value);
	static void DebugToOutput(std::string precursor, float value);
	static void DebugToOutput(float value);
	~Debug();
};

