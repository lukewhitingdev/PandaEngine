#pragma once
#include "Cam.h"
class staticGeneratedCamera : public Cam
{
public:
	staticGeneratedCamera(XMFLOAT3 pos, XMFLOAT3 to, float wWidth, float wHeight, float nearDepth, float farDepth);

	void UpdateStoredFloats();
};

