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
