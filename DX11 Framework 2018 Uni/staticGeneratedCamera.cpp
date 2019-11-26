#include "staticGeneratedCamera.h"
#include <DirectXMath.h>
using namespace DirectX;



staticGeneratedCamera::staticGeneratedCamera(XMFLOAT3 pos, XMFLOAT3 to, float wWidth, float wHeight, float nearDepth, float farDepth)
{
	_eye = pos;
	_to = to;
	_up = XMFLOAT3(0.0f, 1.0f, 0.0f);

	_windowWidth = wWidth;
	_windowHeight = wHeight;
	_nearDepth = nearDepth;
	_farDepth = farDepth;

}

void staticGeneratedCamera::UpdateStoredFloats()
{
	// Store the view matrix
	XMStoreFloat4x4(&_view, XMMatrixLookToLH(XMLoadFloat3(&_eye), XMLoadFloat3(&_to), XMLoadFloat3(&_up)));

	// Store the projection matrix
	XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _windowWidth / (FLOAT)_windowHeight, 0.01f, 100.0f));
}
