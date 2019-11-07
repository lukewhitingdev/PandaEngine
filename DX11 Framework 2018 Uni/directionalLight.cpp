#include "directionalLight.h"


directionalLight::directionalLight(XMFLOAT3 eyePos)
{

	// Initializes light values
	lightDirection = XMFLOAT3(0.5f, 0.0f, -1.0f);
	diffuseMaterial = XMFLOAT4(1.0f, 0.0f, 0.5f, 1.0f);
	diffuseLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	AmbientLight = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.2f);
	AmbientMaterial = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.2f);

	SpecularMtrl = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	SpecularLight = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	SpecularPower = 10.0f;
	EyePosW = XMFLOAT3(0.0f, 0.0f, -3.0f);
}

directionalLight::directionalLight(XMFLOAT3 dir, float specPow)
{

	// Initializes light values
	lightDirection = dir;
	diffuseMaterial = XMFLOAT4(1.0f, 0.0f, 0.5f, 1.0f);
	diffuseLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	AmbientLight = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.2f);
	AmbientMaterial = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.2f);

	SpecularMtrl = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	SpecularLight = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	SpecularPower = specPow;
	EyePosW = XMFLOAT3(0.0f, 0.0f, -3.0f);
}

void directionalLight::Draw(ID3D11DeviceContext* context, ID3D11Buffer*  cBuffer, ConstantBuffer& cb)
{
	// Adds them to the constant buffer
	cb.dirLight.DiffuseLight = diffuseLight;
	cb.dirLight.DiffuseMtrl = diffuseMaterial;
	cb.dirLight.LightVecW = lightDirection;

	cb.dirLight.AmbientLight = AmbientLight;
	cb.dirLight.AmbientMaterial = AmbientMaterial;

	cb.dirLight.SpecularMtrl = SpecularMtrl;
	cb.dirLight.SpecularLight = SpecularLight;
	cb.dirLight.SpecularPower = SpecularPower;
	cb.dirLight.EyePosW = EyePosW;

	// Update the cBuffer with the lighting settings
	context->UpdateSubresource(cBuffer, 0, nullptr, &cb, 0, 0);
}
