#pragma once
#include "Mesh.h"
class cylinder : public Mesh
{
public:
	cylinder(ID3D11Device* device, const wchar_t* texfileName);

	virtual void Update(float time, XMFLOAT3 pos, XMFLOAT3 scale, float yaw);
};

