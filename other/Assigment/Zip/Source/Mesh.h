#pragma once
#include <d3d11_1.h>
#include "Structures.h"
#include "OBJLoader.h"
#include "DDSTextureLoader.h"
class Mesh
{
public:

	enum meshType {
		WAVE,
		STATIC,
		WALL,
		NONE
	};

	// Load the obj files from a constructor and draw and update them from this virtual
	virtual void Draw(ID3D11DeviceContext* context, ID3D11PixelShader* pixelShader, ID3D11VertexShader* vertexShader, ID3D11Buffer* constantBuffer, ConstantBuffer& cb);
	virtual void Update(float time);


	// Game related stuff should move out later
	virtual void setPosition(XMFLOAT3 pos) { position = pos;};
	virtual XMFLOAT3 getPosition() { return position; };
	virtual void setScale(float s) { scale = XMFLOAT3(s, s, s); };
	virtual void setScale(XMFLOAT3 s) { scale = s; };
	virtual XMFLOAT3 getScale() { return scale; };
	virtual void UpdateMovement(float deltaTime);
	virtual bool getObjectPossesionState() { return ObjectPossesed; };
	virtual void setObjectPossesionState(bool state) { ObjectPossesed = state; };
	virtual meshType getMeshType() { return mType; };

	// Mesh Type
	meshType mType = NONE;

protected:
	ID3D11ShaderResourceView* textureResourceView;
	MeshData objMeshLoader;
	UINT stride;
	UINT offset;
	XMFLOAT4X4 objectMatrix;


	bool ObjectPossesed = false;
	XMFLOAT3 scale;
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMMATRIX posMatrix;

		
	XMFLOAT3 lookDir = { 0.0f, 0.0f, 0.0f };
	float speed = 0.000001f;
	float acceleration = 0.0000005f;
	float yaw = 0;
	float pitch = 0;
	float roll = 0;
};

