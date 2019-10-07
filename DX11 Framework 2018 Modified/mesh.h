#pragma once
#include <directxmath.h>
#include <fstream>
#include <istream>
#include <d3d11.h>
#include <vector>
#include <Windows.h>
using namespace DirectX;
using namespace std;

/*

OBJ Loader from: https://www.braynzarsoft.net/viewtutorial/q16390-obj-model-loader; referenced

*/


struct TextureManager {
	vector<ID3D11ShaderResourceView*> TextureList;
	vector<string> TextureNameArray;
};

struct SurfaceMaterial {
	string materialName; // used for matching the subset of the object with its material

	// Material colors
	XMFLOAT4 diffuse;
	XMFLOAT3 ambient;
	XMFLOAT4 specular;

	// Texture id's to lookup textures in the TextureList above
	int diffuseTextureID;
	int ambientTextureID;
	int specularTextureID;
	int alphaTextureID;
	int normalMapTextureID;

	// So we dont implement stuff we dont need, eg. texture styles that dont exist on the obj
	bool hasDiffuseTexture;
	bool hasAmbientTexture;
	bool hasSpecularTexture;
	bool hasAlphaTexture;
	bool hasNormalMap;
	bool isTransparent;
};

struct ObjModel {
	int subSets; // Num of subsets on the model
	ID3D11Buffer* VertexBuffer; // Vertex Buffer
	ID3D11Buffer* IndexBuffer; // Index Buffer
	vector<XMFLOAT3> Vertices; // Stores verts
	vector<DWORD> Indices; // Stores indices
	vector<int> subsetIndexStart; // subset drawing index start
	vector<int> subsetMaterialID; // Subset material ID
	XMMATRIX World; // World matrix, can be replaced soon
	vector<XMFLOAT3> AABB; // Bounding box collision

	XMFLOAT3 Center;
	float BoundingSphere;
};

class mesh
{
	void Mesh();

private:
	std::vector<XMFLOAT4X4> cubeVector;
public:

	// Obj Loading
	bool loadObjModel(ID3D11Device* device, 
						string fileName, 
						ObjModel& model, 
						vector<SurfaceMaterial>& material, 
						TextureManager& textureManager,
						bool computeNormals,
						bool flipFaces);


	// Primative Cube Generation
	void generateCubes(int num);
	void drawCubes(ID3D11DeviceContext* deviceContext, ID3D11Buffer* cBuffer, XMFLOAT4X4& worldMatrix, XMFLOAT4X4& viewMatrix, XMFLOAT4X4& projectionMatrix);
	void updateCubesRotation(float t);
	void updateCube(int cubeNum, int x, int y, int z, float rt);
};

