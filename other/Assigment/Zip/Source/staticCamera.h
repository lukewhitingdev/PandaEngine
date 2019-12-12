#pragma once
#include "Cam.h"
class staticCamera : public Cam
{
public:
	staticCamera(XMFLOAT3 pos, XMFLOAT3 to, float wWidth, float wHeight, float nearDepth, float farDepth);

	void UpdateStoredFloats();
};

