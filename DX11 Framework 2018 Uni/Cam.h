#include <DirectXMath.h>
#include <DirectXColors.h>
#include <d3d11.h>
#include <Windows.h>
using namespace DirectX;
#pragma once
class Cam
{
public:
	Cam();
	~Cam();

	virtual void UpdateStoredFloats();

	virtual void setCameraPos(float x, float y, float z);
	virtual XMFLOAT3 getCameraPos();

	virtual void setLookAtPos(float x, float y, float z);
	virtual XMFLOAT3 getLookAtPos();
	virtual void setLookToPos(float x, float y, float z);
	virtual XMFLOAT3 getLookToPos();
	virtual void setUpPos(float x, float y, float z);
	virtual XMFLOAT3 getUpPos();

	virtual XMFLOAT4X4 getViewMatrix();
	virtual XMFLOAT4X4 getProjectionMatrix();
	virtual XMFLOAT4X4 getViewProjMatrix();

	virtual void Reshape(float wWidth, float wHeight, float nearDepth, float farDepth);

protected:
	XMFLOAT3 _eye;
	XMFLOAT3 _at;
	XMFLOAT3 _to;
	XMFLOAT3 _up;

	float _windowWidth;
	float _windowHeight;
	float _nearDepth;
	float _farDepth;

	XMFLOAT4X4 _view;
	XMFLOAT4X4 _projection;
};

