#include "Mesh.h"



Mesh::Mesh()
{

}

void Mesh::Draw(ID3D11VertexShader* vertShader, ID3D11PixelShader* pixelShader, ID3D11Buffer* conBuffer)
{
	// Virutal Overwrited by inherited objs
}

void Mesh::Update(int deltaTime)
{
	// Virutal Overwrited by inherited objs
}

void Mesh::GenerateMesh(ID3D11Device* D3device, ID3D11Buffer* vertBuffer, ID3D11Buffer* indicesBuffer, ID3D11DeviceContext* context, ConstantBuffer cb)
{
	// Virutal Overwrited by inherited objs
}


Mesh::~Mesh()
{
}
