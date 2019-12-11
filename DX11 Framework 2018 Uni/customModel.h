#pragma once
#include "Mesh.h"
class customModel : public Mesh
{
public:
	customModel(ID3D11Device* device, char* objfileName, bool rHand, meshType mType);
	customModel(ID3D11Device* device, const wchar_t* texfileName, char* objfileName, meshType mType);
	customModel(ID3D11Device* device, const wchar_t* texfileName, char* objfileName, bool rHand);


private:
	int debugTime;
};

