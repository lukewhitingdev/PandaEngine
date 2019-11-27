#include "UtlilityClass.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>



UtlilityClass::UtlilityClass()
{
}


UtlilityClass::~UtlilityClass()
{
}

bool Util::compareXMFLOAT3(XMFLOAT3 first, XMFLOAT3 second)
{
	if (first.x == second.x) {
		if (first.y == second.y) {
			if (first.z == second.z) {
				return true;
			}
		}
	}
	return false;
}

void Util::SaveToCameraPositionsToFile(const char* fileName)
{
	std::ofstream outStream;
	std::ifstream inStream;
	int length;
	inStream.open(fileName);
	// If there is no file then just do it like normal
	if (!inStream.good()) {
		inStream.close();
		outStream.open(fileName);
		outStream << "Output file, Hello World!";
		outStream.close();
	}
	else { // If there is already a file then duplicate it
		// Get the length
		inStream.seekg(0, std::ios_base::beg);
		inStream.seekg(0, std::ios_base::end);
		length = inStream.tellg();

		// File is empty
		if (length <= 0) {

		}
		else {
			std::vector<std::string> savedChars;
			std::string currentLine;
			inStream.seekg(0, std::ios_base::beg);
			// Save all input
			while (std::getline(inStream, currentLine)) {
				savedChars.push_back(currentLine);
			}
			inStream.close();
			outStream.open(fileName);
			if (!outStream.good()) {
				return;
			}

		}

	}
}

void Util::SaveToMeshPositionsToFile()
{
}
