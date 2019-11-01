#pragma once
#include "Mesh.h"
class customModel : public Mesh
{
public:
	customModel(ID3D11Device* device, const wchar_t* texfileName, char* objfileName);
	void Draw(ID3D11DeviceContext* context, ID3D11PixelShader* pixelShader, ID3D11Buffer* constantBuffer, ConstantBuffer& cb);
	void Update(float time, float x, float y, float z);

private:
	ID3D11ShaderResourceView* textureResourceView;
	MeshData objMeshLoader;
	UINT stride;
	UINT offset;
	XMFLOAT4X4 objectMatrix;
};

