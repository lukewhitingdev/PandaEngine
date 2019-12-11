#pragma once
#include "Structures.h"
#include <DirectXColors.h>
#include <DirectXMath.h>
#include <d3d11.h>
class Light
{

public:

	enum LightingTypes {
		DIRECTIONAL,
		SPOT,
		POINT,
		NONE
	};

	virtual void Draw(ID3D11DeviceContext*, ID3D11Buffer*, ConstantBuffer&, XMFLOAT3);
	XMFLOAT3 getPosition() { return EyePosW; };
	virtual LightingTypes getLightType() { return lightType; };

protected:
	XMFLOAT3 EyePosW = { 0, 0, 0 }; // Camera Pos in World
	LightingTypes lightType = NONE;
};


