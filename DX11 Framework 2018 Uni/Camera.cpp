#include "Camera.h"



Camera::Camera(XMFLOAT3 pos, XMFLOAT3 at, XMFLOAT3 up, float wWidth, float wHeight, float nearDepth, float farDepth)
{

	_eye = pos;
	_at = at;
	_up = up;

	_windowWidth = wWidth;
	_windowHeight = wHeight;
	_nearDepth = nearDepth;
	_farDepth = farDepth;
	
}

Camera::~Camera()
{
}

void Camera::Update()
{
	// Store the view matrix
	XMStoreFloat4x4(&_view, XMMatrixLookAtLH(XMLoadFloat3(&_eye), XMLoadFloat3(&_at), XMLoadFloat3(&_up)));

	// Store the projection matrix
	XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _windowWidth / (FLOAT)_windowHeight, 0.01f, 100.0f));
}

void Camera::setCameraPos(float x, float y, float z)
{
	_eye = XMFLOAT3(x, y, z);
}

XMFLOAT3 Camera::getCameraPos()
{
	return _eye;
}


void Camera::setLookAtPos(float x, float y, float z)
{
	_at = XMFLOAT3(x, y, z);
}

XMFLOAT3 Camera::getLookAtPos()
{
	return _at;
}


void Camera::setUpPos(float x, float y, float z)
{
	_up = XMFLOAT3(x, y, z);
}

XMFLOAT3 Camera::getSetUpPos()
{
	return _up;
}

XMFLOAT4X4 Camera::getViewMatrix()
{
	return _view;
}

XMFLOAT4X4 Camera::getProjectionMatrix()
{
	return _projection;
}

XMFLOAT4X4 Camera::getViewProjMatrix()
{
	//TODO: Figure how to combine matrices
	return XMFLOAT4X4();
}


void Camera::Reshape(float wWidth, float wHeight, float nearDepth, float farDepth)
{
	_windowWidth = wWidth;
	_windowHeight = wHeight;
	_nearDepth = nearDepth;
	_farDepth = farDepth;
}
