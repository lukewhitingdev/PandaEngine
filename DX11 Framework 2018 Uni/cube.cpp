#include "cube.h"

cube::cube(ID3D11Device* device, const wchar_t* texfileName)
{
	// Reset the local matrix
	XMStoreFloat4x4(&objectMatrix, XMMatrixIdentity());

	// Get the texture and load the mesh
	CreateDDSTextureFromFile(device, texfileName, nullptr, &textureResourceView);
	objMeshLoader = OBJLoader::Load("Assets/Object Models/Primatives/cube.obj", device);

	// set stride and offsets for later
	stride = objMeshLoader.VBStride;
	offset = objMeshLoader.VBOffset;
}

void cube::Draw(ID3D11DeviceContext* context, ID3D11PixelShader* pixelShader, ID3D11Buffer* constantBuffer, ConstantBuffer& cb)
{
	
	// Transpose the local matrix and pass it to the constant buffer
	XMMATRIX world = XMLoadFloat4x4(&objectMatrix);
	cb.mWorld = XMMatrixTranspose(world);
	context->UpdateSubresource(constantBuffer, 0, nullptr, &cb, 0, 0);

	// Reset the pixel shader texture.
	context->PSSetShaderResources(0, 1, &textureResourceView);
	context->PSSetShader(pixelShader, nullptr, 0);

	// Set buffers and draw.
	context->IASetVertexBuffers(0, 1, &objMeshLoader.VertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(objMeshLoader.IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	context->DrawIndexed(objMeshLoader.IndexCount, 0, 0);
}

void cube::Update(float time, float x, float y, float z)
{
	XMStoreFloat4x4(&objectMatrix, XMMatrixRotationY(time) * XMMatrixTranslation(x, y, z) * XMMatrixScaling(0.6f, 0.6f, 0.6f));
}
