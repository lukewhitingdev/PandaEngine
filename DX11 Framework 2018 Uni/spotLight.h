#pragma once
#include "Light.h"

using namespace DirectX;

class spotLight : public Light
{

public:
	spotLight(XMFLOAT3 lightPos, XMFLOAT3 lightDir, XMFLOAT3 eyePos);

	void Draw(ID3D11DeviceContext* context, ID3D11Buffer* cBuffer, ConstantBuffer& cb, XMFLOAT3 eyePos);

private:
	XMFLOAT4 diffuseLight;
	XMFLOAT4 AmbientLight;
	XMFLOAT4 SpecularLight;

	XMFLOAT3 lightPosition;
	float Range;

	XMFLOAT3 lightDirection;
	float spotPower;

	XMFLOAT3 Attenuation;

	XMFLOAT3 EyePosW; // Camera Pos in World
	Material lightMaterial;
};

