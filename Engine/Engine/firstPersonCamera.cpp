#include "firstPersonCamera.h"



firstPersonCamera::firstPersonCamera(XMFLOAT3 pos, XMFLOAT3 to, XMFLOAT3 up, XMFLOAT3 right, float wWidth, float wHeight, float nearDepth, float farDepth)
{
	_eye = pos;
	_to = to;
	_up = up;
	_right = right;

	_windowWidth = wWidth;
	_windowHeight = wHeight;
	_nearDepth = nearDepth;
	_farDepth = farDepth;

	offset = { 0.0f, 5.0f, -20.0f };

}


firstPersonCamera::~firstPersonCamera()
{
}

void firstPersonCamera::UpdateStoredFloats()
{
	// Store the view matrix
	XMStoreFloat4x4(&_view, XMMatrixLookToLH(XMLoadFloat3(&_eye), XMLoadFloat3(&_to), XMLoadFloat3(&_up)));

	// Store the projection matrix
	XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _windowWidth / (FLOAT)_windowHeight, 0.01f, 100.0f));
}

void firstPersonCamera::updateCameraMovement(std::vector<Cam*>& camVector)
{
	camVector = camVector;
	POINT cursorPoint = getCursorPos();

	if (cursorPoint.x != lastPoint.x && cursorPoint.y != lastPoint.y) {
		XMFLOAT3 eye = getCameraPos();
		XMFLOAT3 at = getLookToPos();
		at.x += -(float)cursorPoint.x / 100;
		at.y += (float)cursorPoint.y / 100;
		setLookToPos(at.x, at.y, at.z);
		UpdateStoredFloats();
	}
}

POINT firstPersonCamera::getCursorPos()
{
	POINT returnPoint;
	// Gets cursor pos
	POINT point;
	GetCursorPos(&point);

	// If the difference has never been calculated
	if (lastPoint.x == NULL) {
		lastPoint = point;
	}

	float diffX = (float)lastPoint.x - (float)point.x;
	float diffY = (float)lastPoint.y - (float)point.y;

	lastPoint = point;

	returnPoint = { (LONG)diffX, (LONG)diffY };

	return returnPoint;
}


