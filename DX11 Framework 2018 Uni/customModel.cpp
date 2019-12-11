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

void customModel::Update(float time)
{
	XMStoreFloat4x4(&objectMatrix, XMMatrixRotationY(yaw) * XMMatrixTranslation(position.x, position.y, position.z) * XMMatrixScaling(scale.x, scale.y, scale.z));
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