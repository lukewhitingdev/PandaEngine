#include "LookToCam.h"



LookToCam::LookToCam(XMFLOAT3 pos, XMFLOAT3 to, XMFLOAT3 up, XMFLOAT3 right, float wWidth, float wHeight, float nearDepth, float farDepth)
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


LookToCam::~LookToCam()
{
}

void LookToCam::UpdateStoredFloats()
{
	// Store the view matrix
	XMStoreFloat4x4(&_view, XMMatrixLookToLH(XMLoadFloat3(&_eye), XMLoadFloat3(&_to), XMLoadFloat3(&_up)));

	// Store the projection matrix
	XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _windowWidth / (FLOAT)_windowHeight, 0.01f, 100.0f));

}

XMFLOAT3 LookToCam::getRight()
{
	XMVECTOR vUp = XMLoadFloat3(&_up);
	XMVECTOR vTo = XMLoadFloat3(&_to);
	XMVECTOR RightCross = XMVector3Cross(vUp, vTo);

	XMStoreFloat3(&_right, RightCross);

	return XMFLOAT3(_right.x, _right.y, _right.z);
}
