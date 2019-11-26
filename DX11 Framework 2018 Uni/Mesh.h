#pragma once
#include <d3d11_1.h>
#include "Structures.h"
#include "OBJLoader.h"
#include "DDSTextureLoader.h"
class Mesh
{
public:
	// Load the obj files from a constructor and draw and update them from this virtual
	virtual void Draw(ID3D11DeviceContext*, ID3D11PixelShader*, ID3D11Buffer*, ConstantBuffer&);
	virtual void Update(float);


	// Game related stuff should move out later
	virtual void setPosition(XMFLOAT3 pos) { position = pos;};
	virtual XMFLOAT3 getPosition() { return position; };
	virtual void setScale(float s) { scale = s; };
	virtual float getScale() { return scale; };
	virtual void UpdateMovement();
	virtual bool getObjectPossesionState() { return ObjectPossesed; };
	virtual void setObjectPossesionState(bool state) { ObjectPossesed = state; };

protected:
	ID3D11ShaderResourceView* textureResourceView;
	MeshData objMeshLoader;
	UINT stride;
	UINT offset;
	XMFLOAT4X4 objectMatrix;


	bool ObjectPossesed = false;
	float scale;
	XMFLOAT3 position;
	XMMATRIX posMatrix;
	XMMATRIX rotation;

	float yaw = 0;
	float pitch = 0;
	float roll = 0;
};

