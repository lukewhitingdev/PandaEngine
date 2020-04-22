#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Cam.h"
#include "GameObject.h"
#include "Light.h"
using namespace std;
class saveToFileManager
{
public:
	saveToFileManager(const char* fileName);
	~saveToFileManager();

	void SavePositionsToFile(vector<GameObject*>& gVector);
	vector<XMFLOAT3> LoadPositionsFromFile();
	void setLoadObjectsFromFile(bool value) { loadObjectsFromFile = value; };
	bool getLoadObjectsFromFile() { return loadObjectsFromFile; };


protected:	

	XMFLOAT3 extractPositionalInfoFromLine(string Line);

	bool loadObjectsFromFile;
	const char* savedFileName;
};

