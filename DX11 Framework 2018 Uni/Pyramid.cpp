#include "Pyramid.h"



Pyramid::Pyramid()
{
	pyramidMesh = new Mesh();
	device = nullptr;
	indexBuffer = nullptr;
	vertexBuffer = nullptr;
	DeviceContext = nullptr;
}

void Pyramid::Draw(ID3D11VertexShader* vertShader, ID3D11PixelShader* pixelShader, ID3D11Buffer* conBuffer)
{
	DeviceContext->VSSetShader(vertShader, nullptr, 0);
	DeviceContext->VSSetConstantBuffers(0, 1, &conBuffer);
	DeviceContext->PSSetConstantBuffers(0, 1, &conBuffer);
	DeviceContext->PSSetShader(pixelShader, nullptr, 0);
	DeviceContext->DrawIndexed(36, 0, 0);
}

void Pyramid::Update()
{
}

void Pyramid::GenerateMesh(ID3D11Device* D3device, ID3D11Buffer* vertBuffer, ID3D11Buffer* indicesBuffer, ID3D11DeviceContext* context)
{
	device = D3device;
	vertexBuffer = vertBuffer;
	indexBuffer = indicesBuffer;
	DeviceContext = context;

	GenerateVertices();
	GenerateIndices();
}


Pyramid::~Pyramid()
{
}

void Pyramid::GenerateIndices()
{
	// Pyramid Vertices

	WORD PyramidIndices[] =
	{
		// Base
		0, 1, 2,
		1, 3, 2,

		// Sides
		0, 4, 1,
		1, 4, 3,
		2, 3, 4,
		0, 2, 4,
	};


	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 18; // Index buffer size
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;


	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = PyramidIndices;
	device->CreateBuffer(&bd, &InitData, &indexBuffer);

	DeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);
}

void Pyramid::GenerateVertices()
{
	// Pyramid Vertices

	SimpleVertex PyramidVertices[] =
	{
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
	};
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 5;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = PyramidVertices;

	device->CreateBuffer(&bd, &InitData, &vertexBuffer);


	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
}
