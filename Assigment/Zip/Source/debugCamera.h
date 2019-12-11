#include "Cam.h"
using namespace DirectX;
#pragma once
class debugCamera : public Cam
{

public:
	debugCamera(XMFLOAT3 pos, XMFLOAT3 to, XMFLOAT3 up, XMFLOAT3 right, float wWidth, float wHeight, float nearDepth, float farDepth);
	~debugCamera();

	void UpdateStoredFloats();

	void updateCameraMovement(std::vector<Cam*>&camVector);

protected:
	// Cursor Input, last point recorded
	POINT lastPoint = { NULL, NULL };

	POINT getCursorPos();
};

