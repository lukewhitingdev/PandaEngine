#include "saveToFileManager.h"



saveToFileManager::saveToFileManager(const char* fileName)
{
	savedFileName = fileName;
}


saveToFileManager::~saveToFileManager()
{
}

void saveToFileManager::SavePositionsToFile(vector<GameObject*> gVector)
{
	ofstream outStream;
	outStream.open(savedFileName);

	// Write all Mesh positions to the text file.
	for (size_t i = 0; i < gVector.size(); i++) {
		XMFLOAT3 currentMeshPos = gVector[i]->getTransformComponent()->getPosition();
		outStream << "mesh" + to_string(i) + " ";
		outStream << "(" + to_string(currentMeshPos.x) + "," + to_string(currentMeshPos.y) + "," + to_string(currentMeshPos.z) + ")";
		outStream << "\n";
	}
	
	// TODO: Add Camera and Light Loading.

	outStream.close();
}

vector<XMFLOAT3> saveToFileManager::LoadPositionsFromFile()
{
	// Read file.
	ifstream inStream;
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
	for (size_t i = 0; i < savedLines.size(); i++) {
		readPositions.push_back(extractPositionalInfoFromLine(savedLines[i]));
	}


	inStream.close();

	// TODO: Output positions vector.

	return readPositions;
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
		// Find the comma in the text.
		firstBreakPos = insideBracesString.find(',', firstBreakPos + 1);

		// Finds the value starting from the last recorded comma.
		string ValueString = insideBracesString.substr(secondBreakPos, firstBreakPos);

		// Finds the decimal point.
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
