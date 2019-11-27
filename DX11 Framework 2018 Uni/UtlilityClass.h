#include <DirectXColors.h>
#include <DirectXMath.h>
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

	void SaveToCameraPositionsToFile(const char* fileName);
	void SaveToMeshPositionsToFile();
}

