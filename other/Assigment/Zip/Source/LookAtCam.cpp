#include "LookAtCam.h"



LookAtCam::LookAtCam(XMFLOAT3 pos, XMFLOAT3 at, XMFLOAT3 up, float wWidth, float wHeight, float nearDepth, float farDepth)
{

	_eye = pos;
	_at = at;
	_up = up;

	_windowWidth = wWidth;
	_windowHeight = wHeight;
	_nearDepth = nearDepth;
	_farDepth = farDepth;
	
}

LookAtCam::~LookAtCam()
{
}

void LookAtCam::UpdateStoredFloats()
{
	// Store the view matrix
	XMStoreFloat4x4(&_view, XMMatrixLookAtLH(XMLoadFloat3(&_eye), XMLoadFloat3(&_at), XMLoadFloat3(&_up)));

	// Store the projection matrix
	XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _windowWidth / (FLOAT)_windowHeight, 0.01f, 100.0f));
}