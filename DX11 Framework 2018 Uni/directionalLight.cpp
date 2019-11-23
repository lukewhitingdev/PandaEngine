#include "directionalLight.h"


directionalLight::directionalLight(XMFLOAT3 eyePos)
{

	// Initializes light values
	lightDirection = XMFLOAT3(0.5f, 0.0f, -1.0f);

	diffuseLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	AmbientLight = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.2f);
	SpecularLight = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	SpecularPower = 20.0f;

	EyePosW = eyePos;

	lightMaterial = lightMaterial.getDefaultMaterial();
}
directionalLight::directionalLight(XMFLOAT3 eyePos, Material inputMaterial)
{

	// Initializes light values
	lightDirection = XMFLOAT3(0.5f, 0.0f, -1.0f);

	diffuseLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	AmbientLight = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.2f);
	SpecularLight = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	SpecularPower = 10.0f;

	EyePosW = eyePos;

	lightMaterial = inputMaterial;

	// Debug
	diffuseMaterial = lightMaterial.mDiffuse;
	AmbientMaterial = lightMaterial.mAmbient;
	SpecularMtrl = lightMaterial.mSpecular;
}

directionalLight::directionalLight(XMFLOAT3 dir, float specPow)
{
	// Initializes light values
	lightDirection = dir;
	diffuseLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	AmbientLight = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.2f);

	SpecularLight = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	SpecularPower = specPow;
	EyePosW = XMFLOAT3(0.0f, 0.0f, -3.0f);

	lightMaterial = lightMaterial.getDefaultMaterial();
}

void directionalLight::Draw(ID3D11DeviceContext* context, ID3D11Buffer*  cBuffer, ConstantBuffer& cb, XMFLOAT3 eyePos)
{
	// Adds them to the constant buffer
	cb.dirLight.DiffuseLight = diffuseLight;
	cb.dirLight.LightVecW = lightDirection;

	cb.dirLight.AmbientLight = AmbientLight;

	cb.dirLight.SpecularLight = SpecularLight;
	cb.dirLight.SpecularPower = SpecularPower;
	cb.EyePosW = eyePos;

	cb.globalMaterial.mAmbient = lightMaterial.mAmbient;
	cb.globalMaterial.mDiffuse = lightMaterial.mDiffuse;
	cb.globalMaterial.mSpecular = lightMaterial.mSpecular;

	// Update the cBuffer with the lighting settings
	context->UpdateSubresource(cBuffer, 0, nullptr, &cb, 0, 0);
}
