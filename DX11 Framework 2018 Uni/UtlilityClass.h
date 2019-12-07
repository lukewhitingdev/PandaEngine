#include <DirectXColors.h>
#include <DirectXMath.h>
#include <vector>
#include "Cam.h"
using namespace DirectX;
#pragma once
class UtlilityClass
{
public:
	UtlilityClass();
	~UtlilityClass();
};

namespace Util {
	bool compareXMFLOAT3(XMFLOAT3 first, XMFLOAT3 second);

	// Save Camera Positions

	void SaveToCameraPositionsToFile(const char* fileName, std::vector<Cam*>& cVector);
	void SaveToMeshPositionsToFile();

}

