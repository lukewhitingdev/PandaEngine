#include <DirectXColors.h>
#include <DirectXMath.h>
#include <d3d11.h>
#include <Windows.h>
#include "Cam.h"
using namespace DirectX;
#pragma once
class LookToCam : public Cam
{

public:
	LookToCam(XMFLOAT3 pos, XMFLOAT3 to, XMFLOAT3 up, XMFLOAT3 right, float wWidth, float wHeight, float nearDepth, float farDepth);
	~LookToCam();

	void UpdateStoredFloats();
};

