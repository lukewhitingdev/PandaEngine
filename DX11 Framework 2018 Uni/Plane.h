#pragma once
#include "Mesh.h"
class Plane : public Mesh
{
public:
	Plane();

	void Draw(ID3D11VertexShader* vertShader, ID3D11PixelShader* pixelShader, ID3D11Buffer* conBuffer);
	void Update();

	void GenerateMesh(ID3D11Device* D3device, ID3D11Buffer* vertBuffer, ID3D11Buffer* indicesBuffer, ID3D11DeviceContext* context);

	~Plane();

private:
	Mesh* objectMesh;
	ID3D11Device* device;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11DeviceContext* DeviceContext;

	void GenerateIndices();
	void GenerateVertices();
};

