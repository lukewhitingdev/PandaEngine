#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <vector>
using namespace DirectX;


class mesh
{
	void Mesh();

private:
	std::vector<XMFLOAT4X4> cubeVector;
public:
	void generateCubes(int num);
	void drawCubes(ID3D11DeviceContext* deviceContext, ID3D11Buffer* cBuffer, XMFLOAT4X4& worldMatrix, XMFLOAT4X4& viewMatrix, XMFLOAT4X4& projectionMatrix);
	void updateCubesRotation(float t);
	void updateCube(int cubeNum, int x, int y, int z, float rt);
};

