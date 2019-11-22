#pragma once
#include <directxmath.h>
#include <directxcolors.h>
#include <cstring>
using namespace DirectX;

struct SimpleVertex
{
	XMFLOAT3 Pos;
	XMFLOAT3 Normal;
	XMFLOAT2 TexC;

	bool operator<(const SimpleVertex other) const {
		return std::memcmp((void*)this, (void*)&other, sizeof(SimpleVertex)) > 0;
	}
};

struct DirectionalLight {
	XMFLOAT4 DiffuseMtrl;
	XMFLOAT4 DiffuseLight;
	XMFLOAT3 LightVecW;
	float pad;

	XMFLOAT4 AmbientLight;
	XMFLOAT4 AmbientMaterial;

	XMFLOAT4 SpecularMtrl;
	XMFLOAT4 SpecularLight;
	float SpecularPower;
	XMFLOAT3 EyePosW; // Camera Pos in World
};

struct ConstantBuffer
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;

	DirectionalLight dirLight;

};

struct Vector3 {
	float x;
	float y;
	float z;
};