#include "Cube.h"



Cube::Cube(int x, int y, int z)
{
	cubeMesh = new Mesh();
	device = nullptr;
	indexBuffer = nullptr;
	vertexBuffer = nullptr;
	DeviceContext = nullptr;
	donePlacement = false;
	initialPosX = x;
	initialPosY = y;
	initialPosZ = z;
	XMStoreFloat4x4(&_worldMatrix, XMMatrixIdentity());
}

void Cube::Draw(ID3D11VertexShader* vertShader, ID3D11PixelShader* pixelShader, ID3D11Buffer* conBuffer)
{

	XMMATRIX world = XMLoadFloat4x4(&_worldMatrix);
	constBuffer.mWorld = XMMatrixTranspose(world);
	DeviceContext->UpdateSubresource(conBuffer, 0, nullptr, &constBuffer, 0, 0);

	DeviceContext->VSSetShader(vertShader, nullptr, 0);
	DeviceContext->VSSetConstantBuffers(0, 1, &conBuffer);
	DeviceContext->PSSetConstantBuffers(0, 1, &conBuffer);
	DeviceContext->PSSetShader(pixelShader, nullptr, 0);
	DeviceContext->DrawIndexed(36, 0, 0);


}

void Cube::Update(int deltaTime)
{
	// TODO: Make it not lag, also make a way to recognise if its a updated pos rather than the initial generation pos

	XMStoreFloat4x4(&_worldMatrix, XMMatrixScaling(0.6f, 0.6f, 0.6f) * XMMatrixTranslation((float)initialPosX, (float)initialPosY, (float)initialPosZ) * XMMatrixRotationX(deltaTime));
}

void Cube::GenerateMesh(ID3D11Device* D3device, ID3D11Buffer* vertBuffer, ID3D11Buffer* indicesBuffer, ID3D11DeviceContext* context, ConstantBuffer cb)
{
	device = D3device;
	vertexBuffer = vertBuffer;
	indexBuffer = indicesBuffer;
	DeviceContext = context;
	constBuffer = cb;

	GenerateVertices();
	GenerateIndices();
}


Cube::~Cube()
{
}

void Cube::GenerateIndices()
{
	// Create index buffer
	WORD CubeIndices[] =
	{
		// Front Face
		0,1,2,
		2,1,3,
		// Back Face
		4,0,6,
		6,0,2,
		// Top Face
		7,5,6,
		6,5,4,
		// Bottom Face
		3,1,7,
		7,1,5,
		// Side Face 1
		4,5,0,
		0,5,1,
		// Side Face 2
		3,7,2,
		2,7,6,
	};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 36; // Index buffer size
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = CubeIndices;
	device->CreateBuffer(&bd, &InitData, &indexBuffer);

	DeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);
}

void Cube::GenerateVertices()
{
	// Create vertex buffer
	SimpleVertex CubeVertices[] =
	{
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },

		{ XMFLOAT3(-1.0f, 1.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
	};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 8;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = CubeVertices;

	device->CreateBuffer(&bd, &InitData, &vertexBuffer);

	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
}
