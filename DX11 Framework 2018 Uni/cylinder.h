#pragma once
#include "Mesh.h"
class cylinder : public Mesh
{
public:
	cylinder(ID3D11Device* device, const wchar_t* texfileName);
	void Draw(ID3D11DeviceContext* context, ID3D11PixelShader* pixelShader, ID3D11Buffer* constantBuffer, ConstantBuffer& cb);
	void Update(float time);

};

