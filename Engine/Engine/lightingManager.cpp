#include "lightingManager.h"



PandaEngine::lightingManager::lightingManager()
{
	resetLighting();
}


PandaEngine::lightingManager::~lightingManager()
{
}

void PandaEngine::lightingManager::addLight(Light* light)
{
	lightVector.push_back(light);
}

void PandaEngine::lightingManager::Draw(ID3D11DeviceContext* context, ID3D11Buffer* cBuffer, ConstantBuffer& cb, XMFLOAT3 eyePos)
{
	for (size_t i = 0; i < lightVector.size(); i++) {
		if (lightVector[i]->getLightType() == currentLightingType || currentLightingType == Light::NONE) {
			lightVector[i]->Draw(context, cBuffer, cb, eyePos);
		}
	}
}

void PandaEngine::lightingManager::enableOnly(Light::LightingTypes type)
{
	currentLightingType = type;
}

void PandaEngine::lightingManager::resetLighting()
{
	currentLightingType = Light::NONE;
}
