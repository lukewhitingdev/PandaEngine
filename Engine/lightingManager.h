#pragma once
#include <vector>
#include "Light.h"
class lightingManager
{
public:

	lightingManager();
	~lightingManager();

	void addLight(Light* light);

	void Draw(ID3D11DeviceContext* context, ID3D11Buffer* cBuffer, ConstantBuffer& cb, XMFLOAT3 eyePos);

	void enableOnly(Light::LightingTypes type);

	void resetLighting();



private: 
	std::vector<Light*> lightVector;

	Light::LightingTypes currentLightingType;
};

