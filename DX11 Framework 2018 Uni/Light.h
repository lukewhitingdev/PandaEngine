#pragma once
#include "Structures.h"
#include <DirectXColors.h>
#include <DirectXMath.h>
#include <d3d11.h>
class Light
{
public:
	virtual void Draw(ID3D11DeviceContext*, ID3D11Buffer*, ConstantBuffer&);
};

