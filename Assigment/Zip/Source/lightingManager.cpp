#include "lightingManager.h"



lightingManager::lightingManager()
{
	resetLighting();
}


lightingManager::~lightingManager()
{
}

void lightingManager::addLight(Light* light)
{
	lightVector.push_back(light);
}

void lightingManager::Draw(ID3D11DeviceContext* context, ID3D11Buffer* cBuffer, ConstantBuffer& cb, XMFLOAT3 eyePos)
{
	for (size_t i = 0; i < lightVector.size(); i++) {
		if (lightVector[i]->getLightType() == currentLightingType || currentLightingType == Light::NONE) {
			lightVector[i]->Draw(context, cBuffer, cb, eyePos);
		}
	}
}

void lightingManager::enableOnly(Light::LightingTypes type)
{
	currentLightingType = type;
}

void lightingManager::resetLighting()
{
	currentLightingType = Light::NONE;
}
