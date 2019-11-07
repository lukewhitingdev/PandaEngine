#include "Cam.h"


void Cam::UpdateStoredFloats()
{
	// Store the view matrix
	XMStoreFloat4x4(&_view, XMMatrixLookAtLH(XMLoadFloat3(&_eye), XMLoadFloat3(&_at), XMLoadFloat3(&_up)));

	// Store the projection matrix
	XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _windowWidth / (FLOAT)_windowHeight, 0.01f, 100.0f));
}

void Cam::setCameraPos(float x, float y, float z)
{
	_eye = XMFLOAT3(x, y, z);
}

XMFLOAT3 Cam::getCameraPos()
{
	return _eye;
}

void Cam::setLookAtPos(float x, float y, float z)
{
	_at = XMFLOAT3(x, y, z);
}

XMFLOAT3 Cam::getLookAtPos()
{
	return _at;
}

void Cam::setLookToPos(float x, float y, float z)
{
	_to = XMFLOAT3(x, y, z);
}

XMFLOAT3 Cam::getLookToPos()
{
	return _to;
}

void Cam::setUpPos(float x, float y, float z)
{
	_up = XMFLOAT3(x, y, z);
}

XMFLOAT3 Cam::getUpPos()
{
	return _up;
}

XMFLOAT4X4 Cam::getViewMatrix()
{
	return _view;
}

XMFLOAT4X4 Cam::getProjectionMatrix()
{
	return _projection;
}

XMFLOAT4X4 Cam::getViewProjMatrix()
{
	//TODO: get combined matrix?
	return XMFLOAT4X4();
}

void Cam::Reshape(float wWidth, float wHeight, float nearDepth, float farDepth)
{
	_windowWidth = wWidth;
	_windowHeight = wHeight;
	_nearDepth = nearDepth;
	_farDepth = farDepth;
}
