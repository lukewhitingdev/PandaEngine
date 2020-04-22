#include "torus.h"

torus::torus(ID3D11Device* device, const wchar_t* texfileName)
{
	// Reset the local matrix
	XMStoreFloat4x4(&objectFloatMatrix, XMMatrixIdentity());

	// Get the texture and load the mesh
	CreateDDSTextureFromFile(device, texfileName, nullptr, &textureResourceView);
	objMeshLoader = OBJLoader::Load("Assets/Object Models/Primatives/torus.obj", device);

	// set stride and offsets for later
	stride = objMeshLoader.VBStride;
	offset = objMeshLoader.VBOffset;
}

void torus::Update(float time, XMFLOAT3 pos, XMFLOAT3 scale, float yaw)
{
	XMStoreFloat4x4(&objectFloatMatrix, XMMatrixRotationY(time) * XMMatrixTranslation(pos.x, pos.y, pos.z) * XMMatrixScaling(scale.x, scale.y, scale.z));
	yaw = yaw;
}
