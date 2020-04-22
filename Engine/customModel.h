#pragma once
#include "Mesh.h"
class customModel : public Mesh
{
public:
	customModel(ID3D11Device* device, char* objfileName, bool rHand, meshType mType);
	customModel(ID3D11Device* device, const wchar_t* texfileName, char* objfileName, meshType mType);
	customModel(ID3D11Device* device, const wchar_t* texfileName, char* objfileName, bool rHand);

	virtual void Update(float time, XMFLOAT3 pos, XMFLOAT3 scale, float yaw);
private:
	int debugTime;
};

