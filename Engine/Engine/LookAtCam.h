#include <DirectXColors.h>
#include <DirectXMath.h>
#include <d3d11.h>
#include <Windows.h>
#include "Cam.h"
using namespace DirectX;
#pragma once
class LookAtCam : public Cam
{

public:
	LookAtCam(XMFLOAT3 pos, XMFLOAT3 at, XMFLOAT3 up, float wWidth, float wHeight, float nearDepth, float farDepth);
	~LookAtCam();

	void UpdateStoredFloats();
};

