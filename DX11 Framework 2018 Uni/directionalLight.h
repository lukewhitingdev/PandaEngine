#pragma once
#include "Light.h"

using namespace DirectX;

class directionalLight : public Light
{

public:
	directionalLight(XMFLOAT3 eyePos);
	directionalLight(XMFLOAT3 dir, float specPow);


	void Draw(ID3D11DeviceContext* context, ID3D11Buffer* cBuffer, ConstantBuffer& cb);

private:
	XMFLOAT3 lightDirection;
	XMFLOAT4 diffuseMaterial;
	XMFLOAT4 diffuseLight;

	XMFLOAT4 AmbientMaterial;
	XMFLOAT4 AmbientLight;

	XMFLOAT4 SpecularMtrl;
	XMFLOAT4 SpecularLight;
	float SpecularPower;
	XMFLOAT3 EyePosW; // Camera Pos in World
};

