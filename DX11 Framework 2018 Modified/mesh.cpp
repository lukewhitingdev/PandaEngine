#include "mesh.h"
#include "Application.h"
using namespace DirectX;

void mesh::Mesh()
{
}

void mesh::generateCubes(int num)
{
	for (int i = 0; i < num; i++) {
		XMFLOAT4X4 newCube;
		cubeVector.push_back(newCube);
	}
}

void mesh::drawCubes(ID3D11DeviceContext* deviceContext, ID3D11Buffer* cBuffer, XMFLOAT4X4& worldMatrix, XMFLOAT4X4& viewMatrix, XMFLOAT4X4& projectionMatrix)
{
	// Initalisation for matrices and buffers
	XMMATRIX world = XMLoadFloat4x4(&worldMatrix);
	XMMATRIX view = XMLoadFloat4x4(&viewMatrix);
	XMMATRIX projection = XMLoadFloat4x4(&projectionMatrix);

	ConstantBuffer cb;
	cb.mWorld = XMMatrixTranspose(world);
	cb.mView = XMMatrixTranspose(view);
	cb.mProjection = XMMatrixTranspose(projection);

	deviceContext->UpdateSubresource(cBuffer, 0, nullptr, &cb, 0, 0);

	// Drawing part
	for (int i = 0; i < cubeVector.size(); i++) {
		world = XMLoadFloat4x4(&cubeVector[i]);
		cb.mWorld = XMMatrixTranspose(world);
		deviceContext->UpdateSubresource(cBuffer, 0, nullptr, &cb, 0, 0);
		deviceContext->DrawIndexed(36, 0, 0);
	}

}

void mesh::updateCubesRotation(float t)
{
	for (int i = 0; i < cubeVector.size(); i++) {
		XMStoreFloat4x4(&cubeVector[i], XMMatrixRotationY(t));
	}
}

void mesh::updateCube(int cubeNum, int x, int y, int z, float rt)
{
	if (cubeNum >= cubeVector.size()) {
		return;
	}
	else {
		XMStoreFloat4x4(&cubeVector[cubeNum], XMMatrixTranslation(x, y, z) * XMMatrixRotationY(rt));
	}
}


