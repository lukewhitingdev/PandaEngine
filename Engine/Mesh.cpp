#include "Mesh.h"

void Mesh::Draw(ID3D11DeviceContext* context, ID3D11PixelShader* pixelShader, ID3D11VertexShader* vertexShader, ID3D11Buffer* constantBuffer, ConstantBuffer& cb)
{
	// Transpose the local matrix and pass it to the constant buffer
	XMStoreFloat4x4(&objectFloatMatrix, objectMatrix);
	cb.mWorld = XMMatrixTranspose(objectMatrix);
	context->UpdateSubresource(constantBuffer, 0, nullptr, &cb, 0, 0);

	// Reset the pixel shader texture.
	context->PSSetShaderResources(0, 1, &textureResourceView);
	context->PSSetShader(pixelShader, nullptr, 0);

	// Set the vertex buffer
	context->VSSetShader(vertexShader, nullptr, 0);

	// Set buffers and draw.
	context->IASetVertexBuffers(0, 1, &objMeshLoader.VertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(objMeshLoader.IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	context->DrawIndexed(objMeshLoader.IndexCount, 0, 0);
}

void Mesh::Update(float time, XMFLOAT3 pos, XMFLOAT3 scale, float yaw)
{
	XMStoreFloat4x4(&objectFloatMatrix, XMMatrixRotationY(time) * XMMatrixTranslation(pos.x, pos.y, pos.z) * XMMatrixScaling(scale.x, scale.y, scale.z));
}
