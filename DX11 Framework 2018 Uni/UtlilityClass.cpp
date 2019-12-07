#include "UtlilityClass.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;



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

void Util::SaveToCameraPositionsToFile(const char* fileName, std::vector<Cam*>& cVector)
{
	ofstream outStream;
	ifstream inStream;
	int length;
	inStream.open(fileName);
	// If there is no file then just do it like normal
	if (!inStream.good()) {
		inStream.close();
		outStream.open(fileName);

		// Write all camera positions to the text file.
		for (int i = 0; i < cVector.size(); i++) {
			XMFLOAT3 currentCamPos = cVector[i]->getCameraPos();
			outStream << "camera" + to_string(i) + " ";
			outStream << "(" + to_string(currentCamPos.x) + "," + to_string(currentCamPos.y) + "," + to_string(currentCamPos.z) + ")";
			outStream << "\n";
		}

		outStream.close();
	}
	else { // If there is already a file then duplicate it
		// Get the length
		inStream.seekg(0, ios_base::beg);
		inStream.seekg(0, ios_base::end);
		length = inStream.tellg();

		// File is empty
		if (length <= 0) {
			// Write it to the file (duplicate)
			inStream.close();
			outStream.open(fileName);
			// Write all camera positions to the text file.
			for (int i = 0; i < cVector.size(); i++) {
				XMFLOAT3 currentCamPos = cVector[i]->getCameraPos();
				outStream << "camera" + to_string(i) + " ";
				outStream << "(" + to_string(currentCamPos.x) + "," + to_string(currentCamPos.y) + "," + to_string(currentCamPos.z) + ")";
				outStream << "\n";
			}
			outStream.close();
		}
		else {
			// Save the current files lines.
			vector<string> savedLines;
			string currentLine;
			inStream.seekg(0, ios_base::beg);
			// Save all input
			while (std::getline(inStream, currentLine)) {
				savedLines.push_back(currentLine);
			}			
			// Start to write the backup
			inStream.close();
			outStream.open("backupPositions.txt");
			// Write all camera positions to the text file.
			for (int i = 0; i < savedLines.size(); i++) {
				outStream << savedLines[i] + "\n";
			}
			outStream.close();
		}

	}
}

void Util::SaveToMeshPositionsToFile()
{
}
