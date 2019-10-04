#include "mesh.h"
#include "Application.h"
using namespace DirectX;

void mesh::Mesh()
{
}

void mesh::drawCube(ID3D11DeviceContext* deviceContext, ID3D11Buffer* cBuffer, XMFLOAT4X4& worldMatrix, XMFLOAT4X4& viewMatrix, XMFLOAT4X4& projectionMatrix)
{
	XMMATRIX world = XMLoadFloat4x4(&worldMatrix);
	XMMATRIX view = XMLoadFloat4x4(&viewMatrix);
	XMMATRIX projection = XMLoadFloat4x4(&projectionMatrix);

	ConstantBuffer cb;
	cb.mWorld = XMMatrixTranspose(world);
	cb.mView = XMMatrixTranspose(view);
	cb.mProjection = XMMatrixTranspose(projection);

	deviceContext->UpdateSubresource(cBuffer, 0, nullptr, &cb, 0, 0);

	world = XMLoadFloat4x4(&_cubeMatrix);
	cb.mWorld = XMMatrixTranspose(world);
	deviceContext->UpdateSubresource(cBuffer, 0, nullptr, &cb, 0, 0);
	deviceContext->DrawIndexed(36, 0, 0);
}

void mesh::updateCube(float t)
{
	XMStoreFloat4x4(&_cubeMatrix, XMMatrixTranslation(6.0f, 0.0f, 0.0f) * XMMatrixScaling(0.3f, 0.3f, 0.3f) * XMMatrixRotationY(t));
}
