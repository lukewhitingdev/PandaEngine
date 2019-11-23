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
	XMFLOAT4 pad1; // Padding for where materials used to be, fix later
	XMFLOAT4 DiffuseLight;
	XMFLOAT3 LightVecW;
	float pad;

	XMFLOAT4 AmbientLight;
	XMFLOAT4 pad2;

	XMFLOAT4 pad3;
	XMFLOAT4 SpecularLight;
	float SpecularPower;
	XMFLOAT3 pad4;
};

struct Material {
	XMFLOAT4 mSpecular;
	XMFLOAT4 mAmbient;
	XMFLOAT4 mDiffuse;

	Material getDefaultMaterial() {
		Material output;
		output.mSpecular = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
		output.mAmbient = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.2f);
		output.mDiffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		return output;
	}
};

struct ConstantBuffer
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;

	DirectionalLight dirLight;

	Material globalMaterial;

	XMFLOAT3 EyePosW; // Camera Pos in World

};

struct Vector3 {
	float x;
	float y;
	float z;
};