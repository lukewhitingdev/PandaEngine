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
	virtual void Update(float, float, float, float);
};

