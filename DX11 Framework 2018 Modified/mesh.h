#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
using namespace DirectX;


class mesh
{
	void Mesh();

private:
	XMFLOAT4X4 _cubeMatrix;
public:
	void drawCube(ID3D11DeviceContext* deviceContext, ID3D11Buffer* cBuffer, XMFLOAT4X4& worldMatrix, XMFLOAT4X4& viewMatrix, XMFLOAT4X4& projectionMatrix);
	void updateCube(float t);
};

