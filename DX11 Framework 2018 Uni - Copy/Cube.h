#pragma once
#include "Mesh.h"


class Cube : public Mesh
{
public:
	Cube(int x, int y, int z);

	void Draw(ID3D11VertexShader* vertShader, ID3D11PixelShader* pixelShader, ID3D11Buffer* conBuffer);
	void Update(int deltaTime);

	void GenerateMesh(ID3D11Device* D3device, ID3D11Buffer* vertBuffer, ID3D11Buffer* indicesBuffer, ID3D11DeviceContext* context, ConstantBuffer cb);

	~Cube();

private:
	Mesh* cubeMesh;
	ID3D11Device* device;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11DeviceContext* DeviceContext;

	void GenerateIndices();
	void GenerateVertices();

	bool donePlacement;
	int initialPosX;
	int initialPosY;
	int initialPosZ;

	ConstantBuffer constBuffer;

	XMFLOAT4X4 _worldMatrix;
};

