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

void cube::Update(float time)
{
	XMStoreFloat4x4(&objectMatrix, XMMatrixRotationY(time) * XMMatrixTranslation(position.x, position.y, position.z) * XMMatrixScaling(scale.x, scale.y, scale.z));
}