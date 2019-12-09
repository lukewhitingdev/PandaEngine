#include "saveToFileManager.h"



saveToFileManager::saveToFileManager(const char* fileName)
{
	savedFileName = fileName;
}


saveToFileManager::~saveToFileManager()
{
}

void saveToFileManager::SavePositionsToFile(vector<Cam*>& cVector, vector<Mesh*>& mVector, vector<Light*>& lVector)
{
	ofstream outStream;
	int length;
	outStream.open(savedFileName);

	// Write all Mesh positions to the text file.
	for (int i = 0; i < mVector.size(); i++) {
		XMFLOAT3 currentMeshPos = mVector[i]->getPosition();
		outStream << "mesh" + to_string(i) + " ";
		outStream << "(" + to_string(currentMeshPos.x) + "," + to_string(currentMeshPos.y) + "," + to_string(currentMeshPos.z) + ")";
		outStream << "\n";
	}
	
	// TODO: Add Camera and Light Loading.

	outStream.close();

	/*	else { // If there is already a file then duplicate it
		// Get the length
		inStream.seekg(0, ios_base::beg);
		inStream.seekg(0, ios_base::end);
		length = inStream.tellg();

		// File is empty
		if (length <= 0) {
			// Write it to the file (duplicate)
			inStream.close();
			outStream.open(savedFileName);
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
		} */
}

void saveToFileManager::LoadPositionsFromFile()
{
	// Read file.
	ifstream inStream;
	int length;
	vector<string> savedLines;
	vector<XMFLOAT3> readPositions;
	string currentLine;
	inStream.open(savedFileName);

	// Push inStream seek to beginning
	inStream.seekg(0, ios_base::beg);
	// Save all input
	while (std::getline(inStream, currentLine)) {
		savedLines.push_back(currentLine);
	}

	// Extract the positions from the file
	for (int i = 0; i < savedLines.size(); i++) {
		readPositions.push_back(extractPositionalInfoFromLine(savedLines[i]));
	}

	// TODO: Output positions vector.

	inStream.close();
}

XMFLOAT3 saveToFileManager::extractPositionalInfoFromLine(string Line)
{
	// Find the brackets containing the positions
	int firstBreakPos = Line.find('(', 0);
	int secondBreakPos = Line.find(')', firstBreakPos);

	string insideBracesString = Line.substr(firstBreakPos, secondBreakPos);

	XMFLOAT3 output;

	vector<float> outputFloats;

	// Find the first value

	firstBreakPos = 0;
	secondBreakPos = 0;

	for (int i = 0; i < 3; i++) {
		firstBreakPos = insideBracesString.find(',', firstBreakPos + 1);

		string ValueString = insideBracesString.substr(secondBreakPos, firstBreakPos);

		secondBreakPos = ValueString.find('.', 0);

		// We have got the first value to 1 decimal place.

		string condencedValue = ValueString.substr(1, secondBreakPos + 2);

		float Value = stof(condencedValue);

		outputFloats.push_back(Value);

		secondBreakPos = firstBreakPos;
	}

	output.x = outputFloats[0];
	output.y = outputFloats[1];
	output.z = outputFloats[2];

	return output;
}
