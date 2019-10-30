#include "Plane.h"



Plane::Plane()
{
	objectMesh = new Mesh();
	device = nullptr;
	indexBuffer = nullptr;
	vertexBuffer = nullptr;
	DeviceContext = nullptr;
}

void Plane::Draw(ID3D11VertexShader* vertShader, ID3D11PixelShader* pixelShader, ID3D11Buffer* conBuffer)
{
	DeviceContext->VSSetShader(vertShader, nullptr, 0);
	DeviceContext->VSSetConstantBuffers(0, 1, &conBuffer);
	DeviceContext->PSSetConstantBuffers(0, 1, &conBuffer);
	DeviceContext->PSSetShader(pixelShader, nullptr, 0);
	DeviceContext->DrawIndexed(36, 0, 0);
}

void Plane::Update()
{
}

void Plane::GenerateMesh(ID3D11Device* D3device, ID3D11Buffer* vertBuffer, ID3D11Buffer* indicesBuffer, ID3D11DeviceContext* context)
{
	device = D3device;
	vertexBuffer = vertBuffer;
	indexBuffer = indicesBuffer;
	DeviceContext = context;

	GenerateVertices();
	GenerateIndices();
}


Plane::~Plane()
{
}

void Plane::GenerateIndices()
{
	// Create index buffer
	WORD PlaneIndices[] =
	{
		// First Face
		0, 2, 1,
		1, 2, 3,
	};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 6; // Index buffer size
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = PlaneIndices;
	device->CreateBuffer(&bd, &InitData, &indexBuffer);

	DeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);
}

void Plane::GenerateVertices()
{	// Pyramid Vertices

	SimpleVertex PlaneVertices[] =
	{
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
	};
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = PlaneVertices;

	device->CreateBuffer(&bd, &InitData, &vertexBuffer);


	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
}
