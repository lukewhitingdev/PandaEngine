#pragma once
#include "Mesh.h"
class cube : public Mesh
{
public:
	cube(ID3D11Device* device, const wchar_t* texfileName);
};

