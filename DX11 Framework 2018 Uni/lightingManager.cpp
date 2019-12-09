#include "lightingManager.h"



lightingManager::lightingManager()
{
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
	for (int i = 0; i < lightVector.size(); i++) {
		lightVector[i]->Draw(context, cBuffer, cb, eyePos);
	}
}
