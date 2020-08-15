#include "spotLight.h"


spotLight::spotLight(XMFLOAT3 lightPos, XMFLOAT3 lightDir, XMFLOAT3 eyePos)
{
	lightType = SPOT;

	// Initializes light values

	AmbientLight = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	diffuseLight = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	SpecularLight = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);

	lightPosition = lightPos;
	Range = 25.0f;

	lightDirection = lightDir;
	spotPower = 5.0f;

	Attenuation = XMFLOAT3(0.0f, 1.0f, 0.0f);

	EyePosW = eyePos;

	lightMaterial = lightMaterial.getDefaultMaterial();
}

void spotLight::Draw(ID3D11DeviceContext* context, ID3D11Buffer* cBuffer, ConstantBuffer& cb, XMFLOAT3 eyePos)
{
	// Adds them to the constant buffer
	cb.spotLight.AmbientLight = AmbientLight;
	cb.spotLight.DiffuseLight = diffuseLight;
	cb.spotLight.SpecularLight = SpecularLight;
	cb.spotLight.LightPos = lightPosition;
	cb.spotLight.LightRange = Range;
	cb.spotLight.lightDirection = lightDirection;
	cb.spotLight.spotPower = spotPower;
	cb.spotLight.Attenuation = Attenuation;
	cb.EyePosW = eyePos;

	cb.globalMaterial.mAmbient = lightMaterial.mAmbient;
	cb.globalMaterial.mDiffuse = lightMaterial.mDiffuse;
	cb.globalMaterial.mSpecular = lightMaterial.mSpecular;

	// Update the cBuffer with the lighting settings
	context->UpdateSubresource(cBuffer, 0, nullptr, &cb, 0, 0);
}
