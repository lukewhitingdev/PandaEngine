#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <array>
using namespace DirectX;
class Mesh
{

public:

	struct SimpleVertex
	{
		XMFLOAT3 Pos;
		XMFLOAT4 Color;
	};

	struct ConstantBuffer
	{
		XMMATRIX mWorld;
		XMMATRIX mView;
		XMMATRIX mProjection;
		float time;
	};

	Mesh();

	virtual void Draw(ID3D11VertexShader* vertShader, ID3D11PixelShader* pixelShader, ID3D11Buffer* conBuffer);
	virtual void Update(int deltaTime);

	virtual void GenerateMesh(ID3D11Device* D3device, ID3D11Buffer* vertBuffer, ID3D11Buffer* indicesBuffer, ID3D11DeviceContext* context, ConstantBuffer cb);

	~Mesh();
};

