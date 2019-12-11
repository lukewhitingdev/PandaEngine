#pragma once
#include "Mesh.h"
class sphere : public Mesh
{
public:
	sphere(ID3D11Device* device, const wchar_t* texfileName);
};

