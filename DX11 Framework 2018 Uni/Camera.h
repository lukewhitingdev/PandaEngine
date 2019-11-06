#include <DirectXColors.h>
#include <DirectXMath.h>
#include <d3d11.h>
#include <Windows.h>
using namespace DirectX;
#pragma once
class Camera
{

private:
	XMFLOAT3 _eye;
	XMFLOAT3 _at;
	XMFLOAT3 _up;

	float _windowWidth;
	float _windowHeight;
	float _nearDepth;
	float _farDepth;

	XMFLOAT4X4 _view;
	XMFLOAT4X4 _projection;

public:
	Camera(XMFLOAT3 pos, XMFLOAT3 at, XMFLOAT3 up, float wWidth, float wHeight, float nearDepth, float farDepth);
	~Camera();

	void Update();

	void setCameraPos(float x, float y, float z);
	XMFLOAT3 getCameraPos();
	void setLookAtPos(float x, float y, float z);
	XMFLOAT3 getLookAtPos();
	void setUpPos(float x, float y, float z);
	XMFLOAT3 getSetUpPos();

	XMFLOAT4X4 getViewMatrix();
	XMFLOAT4X4 getProjectionMatrix();
	XMFLOAT4X4 getViewProjMatrix();

	void Reshape(float wWidth, float wHeight, float nearDepth, float farDepth);
};

