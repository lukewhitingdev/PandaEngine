#pragma once
#include "Mesh.h"
class cube : public Mesh
{
public:
	cube(ID3D11Device* device, const wchar_t* texfileName);
	void Draw(ID3D11DeviceContext* context, ID3D11PixelShader* pixelShader, ID3D11VertexShader* vertexShader, ID3D11Buffer* constantBuffer, ConstantBuffer& cb);
	void Update(float time);

};

