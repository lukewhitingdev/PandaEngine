#include "emptyObject.h"



emptyObject::emptyObject()
{
	objectMesh = new Mesh();
	device = nullptr;
	indexBuffer = nullptr;
	vertexBuffer = nullptr;
	DeviceContext = nullptr;
}

void emptyObject::Draw(ID3D11VertexShader* vertShader, ID3D11PixelShader* pixelShader, ID3D11Buffer* conBuffer)
{
}

void emptyObject::Update()
{
}

void emptyObject::GenerateMesh(ID3D11Device* D3device, ID3D11Buffer* vertBuffer, ID3D11Buffer* indicesBuffer, ID3D11DeviceContext* context)
{
}


emptyObject::~emptyObject()
{
}

void emptyObject::GenerateIndices()
{
}

void emptyObject::GenerateVertices()
{
}
