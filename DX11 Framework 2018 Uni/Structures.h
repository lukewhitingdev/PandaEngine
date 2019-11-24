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

	// 12 + 4 = 16
	XMFLOAT4 AmbientLight; // 16
	XMFLOAT4 DiffuseLight; // 16
	XMFLOAT4 SpecularLight; // 16
	XMFLOAT3 LightVecW; // 12
	float SpecularPower; // 4
};

struct PointLight
{
	XMFLOAT4 AmbientLight; // 16
	XMFLOAT4 DiffuseLight; // 16
	XMFLOAT4 SpecularLight; // 16

	// Packed together
	XMFLOAT3 LightPos; // 12
	float LightRange; // 4

	// Packet together
	XMFLOAT3 Attenuation; // 12
	float pad; // 4

};

struct SpotLight {
	XMFLOAT4 AmbientLight; // 16
	XMFLOAT4 DiffuseLight; // 16
	XMFLOAT4 SpecularLight; // 16

	// Packed together
	XMFLOAT3 LightPos; // 12
	float LightRange; // 4

	// Packed Together
	XMFLOAT3 lightDirection; // 12
	float spotPower; // 4

	// Packet together
	XMFLOAT3 Attenuation; // 12
	float pad; // 4
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

	PointLight pointLight;

	SpotLight spotLight;

	Material globalMaterial;

	XMFLOAT3 EyePosW; // Camera Pos in World

};

struct Vector3 {
	float x;
	float y;
	float z;
};