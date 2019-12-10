#include "customModel.h"

customModel::customModel(ID3D11Device* device, const wchar_t* texfileName, char* objfileName, meshType meshType)
{
	mType = meshType;
	// Reset the local matrix
	XMStoreFloat4x4(&objectMatrix, XMMatrixIdentity());

	// Get the texture and load the mesh
	CreateDDSTextureFromFile(device, texfileName, nullptr, &textureResourceView);
	objMeshLoader = OBJLoader::Load(objfileName, device);

	// set stride and offsets for later
	stride = objMeshLoader.VBStride;
	offset = objMeshLoader.VBOffset;
}

customModel::customModel(ID3D11Device* device, const wchar_t* texfileName, char* objfileName, bool rHand)
{
	// Reset the local matrix
	XMStoreFloat4x4(&objectMatrix, XMMatrixIdentity());

	// Get the texture and load the mesh
	CreateDDSTextureFromFile(device, texfileName, nullptr, &textureResourceView);
	objMeshLoader = OBJLoader::Load(objfileName, device, rHand);

	// set stride and offsets for later
	stride = objMeshLoader.VBStride;
	offset = objMeshLoader.VBOffset;
}

customModel::customModel(ID3D11Device* device, char* objfileName, bool rHand, meshType meshType)
{
	mType = meshType;
	// Reset the local matrix
	XMStoreFloat4x4(&objectMatrix, XMMatrixIdentity());

	// Get the texture and load the mesh
	CreateDDSTextureFromFile(device, L"Assets/Textures/Debug/defaultTex.dds", nullptr, &textureResourceView);
	objMeshLoader = OBJLoader::Load(objfileName, device, rHand);

	// set stride and offsets for later
	stride = objMeshLoader.VBStride;
	offset = objMeshLoader.VBOffset;
}

void customModel::Draw(ID3D11DeviceContext* context, ID3D11PixelShader* pixelShader, ID3D11VertexShader* vertexShader, ID3D11Buffer* constantBuffer, ConstantBuffer& cb)
{

	// Transpose the local matrix and pass it to the constant buffer
	XMMATRIX world = XMLoadFloat4x4(&objectMatrix);
	cb.mWorld = XMMatrixTranspose(world);
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

void customModel::Update(float time)
{
	XMStoreFloat4x4(&objectMatrix, XMMatrixRotationY(yaw) * XMMatrixTranslation(position.x, position.y, position.z) * XMMatrixScaling(scale, scale, scale));
	debugTime = time;
}
