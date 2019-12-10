#pragma once
#include "Mesh.h"
class customModel : public Mesh
{
public:
	customModel(ID3D11Device* device, char* objfileName, bool rHand);
	customModel(ID3D11Device* device, const wchar_t* texfileName, char* objfileName);
	customModel(ID3D11Device* device, const wchar_t* texfileName, char* objfileName, bool rHand);
	void Draw(ID3D11DeviceContext* context, ID3D11PixelShader* pixelShader, ID3D11Buffer* constantBuffer, ConstantBuffer& cb);
	void Update(float time);


private:
	int debugTime;
};

