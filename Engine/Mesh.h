#pragma once
#include <d3d11_1.h>
#include "Structures.h"
#include "OBJLoader.h"
#include "DDSTextureLoader.h"
class Mesh
{

public:

	enum meshType {
		WAVE,
		STATIC,
		WALL,
		NONE
	};

	// Load the obj files from a constructor and draw and update them from this virtual
	virtual void Draw(ID3D11DeviceContext* context, ID3D11PixelShader* pixelShader, ID3D11VertexShader* vertexShader, ID3D11Buffer* constantBuffer, ConstantBuffer& cb);
	virtual void Update(float time, XMFLOAT3 pos, XMFLOAT3 scale, float yaw);

	virtual meshType getMeshType() { return mType; };
	virtual void setMeshType(meshType value) { mType = value; };


protected:
	ID3D11ShaderResourceView* textureResourceView;
	MeshData objMeshLoader;
	UINT stride;
	UINT offset;
	XMFLOAT4X4 objectMatrix;

	// Mesh Type
	meshType mType = NONE;

};

