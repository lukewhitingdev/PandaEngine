#include "mesh.h"
#include "Application.h"
using namespace DirectX;

void mesh::Mesh()
{
}

bool mesh::loadObjModel(ID3D11Device* device, string fileName, ObjModel& model, vector<SurfaceMaterial>& material, TextureManager& textureManager, bool computeNormals, bool flipFaces)
{
	HRESULT hr = 0;

	ifstream fileIn(fileName.c_str()); // Open the file
	string meshMaterialLibary; // Holds the obj material libary filename (example.mtl)

	// Stores object model info
	vector<DWORD> indices;
	vector<XMFLOAT3> vertexPos;
	vector<XMFLOAT3> vertexNorm;
	vector<XMFLOAT2> vertexTexCoords;
	vector<string> meshMaterials;

	// Indices for drawing
	vector<int> vertexPosIndex;
	vector<int> vertexNormalsIndex;
	vector<int> vertexTexCoordsIndex;

	// Reset for if the obj has no textures
	bool hasTexCoord = false;
	bool hasNorm = false;
	
	// Temporary vars for storing stuff in the vectors
	string meshMaterialsTemp;
	int vertexPosIndexTemp;
	int vertNormIndexTemp;
	int vertTextureCoordTemp;

	wchar_t checkChar; // Will store the latest char from the file
	string face; // Holds the string of face vertices
	int vertexIndex = 0; // Counts how many vertices are being loaded
	int triangleCount = 0; // How many triangles are being loaded / PolyCount
	int totalVerts = 0;
	int meshTraingles = 0;
	bool ang = false;

	// See if the file is openable
	if (!fileIn) {
		// Cannot open file
		MessageBox(NULL, L"ERROR", L"Could not open OBJ file!", MB_OK);
		return false;
	}
	while (fileIn) {
		checkChar = fileIn.get(); // Get the next char
		switch (checkChar) {
			// Skip comments
			case '#':
				checkChar = fileIn.get();
				while (checkChar != ' ') {
					checkChar = fileIn.get();
				}
				break;
			
			// Store vertex positions
			case 'v':
				checkChar = fileIn.get();

				// if there is a space appended then they are vertices store em
				if (checkChar == ' ') { 
					float vertZ, vertY, vertX;
					fileIn >> vertX >> vertY >> vertZ;

					vertexPos.push_back(XMFLOAT3(vertX, vertY, vertZ)); // Using left handed coord system so no need to invert
				}

				// if there is a t, then they are texture coordinates (vt)
				if (checkChar == 't') {
					float vertTexZ, vertTexY, vertTexX;
					fileIn >> vertTexX >> vertTexY >> vertTexZ;

					vertexPos.push_back(XMFLOAT3(vertTexX, vertTexY, vertTexZ)); 
					hasTexCoord = true; // Model uses texture coordinates
				}

				// if there is a n, then they are vertexNormals (vn)
				if (checkChar == 'n') {
					float vertNormZ, vertNormY, vertNormX;
					fileIn >> vertNormX >> vertNormY >> vertNormZ;

					vertexPos.push_back(XMFLOAT3(vertNormX, vertNormY, vertNormZ));
					hasNorm = true; // Model uses normal Coordinates
				}

				break;
		}
	}
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


