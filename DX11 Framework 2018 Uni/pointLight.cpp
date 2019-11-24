#include "pointLight.h"


pointLight::pointLight(XMFLOAT3 lightPos, XMFLOAT3 eyePos)
{

	// Initializes light values
	lightPosition = lightPos;

	AmbientLight = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	diffuseLight = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	SpecularLight = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	Range = 25.0f;

	Attenuation = XMFLOAT3(0.0f, 1.0f, 0.0f);

	EyePosW = eyePos;

	lightMaterial = lightMaterial.getDefaultMaterial();
}

void pointLight::Draw(ID3D11DeviceContext* context, ID3D11Buffer* cBuffer, ConstantBuffer& cb, XMFLOAT3 eyePos)
{
	// Adds them to the constant buffer
	cb.pointLight.AmbientLight = AmbientLight;
	cb.pointLight.DiffuseLight = diffuseLight;
	cb.pointLight.SpecularLight = SpecularLight;
	cb.pointLight.LightPos = lightPosition;
	cb.pointLight.LightRange = Range;
	cb.pointLight.Attenuation = Attenuation;
	cb.EyePosW = eyePos;

	cb.globalMaterial.mAmbient = lightMaterial.mAmbient;
	cb.globalMaterial.mDiffuse = lightMaterial.mDiffuse;
	cb.globalMaterial.mSpecular = lightMaterial.mSpecular;

	// Update the cBuffer with the lighting settings
	context->UpdateSubresource(cBuffer, 0, nullptr, &cb, 0, 0);
}
