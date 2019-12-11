#include "debugCamera.h"



debugCamera::debugCamera(XMFLOAT3 pos, XMFLOAT3 to, XMFLOAT3 up, XMFLOAT3 right, float wWidth, float wHeight, float nearDepth, float farDepth)
{
	_eye = pos;
	_to = to;
	_up = up;
	_right = right;

	_windowWidth = wWidth;
	_windowHeight = wHeight;
	_nearDepth = nearDepth;
	_farDepth = farDepth;

}


debugCamera::~debugCamera()
{
}

void debugCamera::UpdateStoredFloats()
{
	// Store the view matrix
	XMStoreFloat4x4(&_view, XMMatrixLookToLH(XMLoadFloat3(&_eye), XMLoadFloat3(&_to), XMLoadFloat3(&_up)));

	// Store the projection matrix
	XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _windowWidth / (FLOAT)_windowHeight, 0.01f, 100.0f));
}

void debugCamera::updateCameraMovement(std::vector<Cam*>& camVector)
{
	POINT cursorPoint = getCursorPos();

	if (cursorPoint.x != lastPoint.x && cursorPoint.y != lastPoint.y) {
		XMFLOAT3 eye = getCameraPos();
		XMFLOAT3 at = getLookToPos();
		at.x += -(float)cursorPoint.x / 100;
		at.y += (float)cursorPoint.y / 100;
		setLookToPos(at.x, at.y, at.z);
		UpdateStoredFloats();
	}
	if (GetAsyncKeyState('W')) {
		XMFLOAT3 eye = getCameraPos();
		XMFLOAT3 at = getLookToPos();

		XMVECTOR speed = XMVectorReplicate(0.005f);
		XMVECTOR look = XMLoadFloat3(&at);
		XMVECTOR position = XMLoadFloat3(&eye);
		XMStoreFloat3(&eye, XMVectorMultiplyAdd(speed, look, position));
		setCameraPos(eye.x, eye.y, eye.z);
		UpdateStoredFloats();
	}
	if (GetAsyncKeyState('S')) {

		XMFLOAT3 eye = getCameraPos();
		XMFLOAT3 at = getLookToPos();

		XMVECTOR speed = XMVectorReplicate(-0.005f);
		XMVECTOR look = XMLoadFloat3(&at);
		XMVECTOR position = XMLoadFloat3(&eye);
		XMStoreFloat3(&eye, XMVectorMultiplyAdd(speed, look, position));
		setCameraPos(eye.x, eye.y, eye.z);
		UpdateStoredFloats();
	}

	if (GetAsyncKeyState('A')) {
		XMFLOAT3 eye = getCameraPos();
		XMFLOAT3 camRight = getRight();

		XMVECTOR speed = XMVectorReplicate(-0.005f);
		XMVECTOR right = XMLoadFloat3(&camRight);
		XMVECTOR position = XMLoadFloat3(&eye);
		XMStoreFloat3(&eye, XMVectorMultiplyAdd(speed, right, position));
		setCameraPos(eye.x, eye.y, eye.z);
		UpdateStoredFloats();
	}

	if (GetAsyncKeyState('D')) {
		XMFLOAT3 eye = getCameraPos();
		XMFLOAT3 camRight = getRight();

		XMVECTOR speed = XMVectorReplicate(0.005f);
		XMVECTOR right = XMLoadFloat3(&camRight);
		XMVECTOR position = XMLoadFloat3(&eye);
		XMStoreFloat3(&eye, XMVectorMultiplyAdd(speed, right, position));
		setCameraPos(eye.x, eye.y, eye.z);
		UpdateStoredFloats();
	}

	if ((GetAsyncKeyState('8'))) {
		camVector[2]->setCameraPos(getCameraPos().x, getCameraPos().y, getCameraPos().z);
		camVector[2]->setLookToPos(getLookToPos().x, getLookToPos().y, getLookToPos().z);
	}
}

POINT debugCamera::getCursorPos()
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


