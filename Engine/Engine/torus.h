#pragma once
#include "Mesh.h"
__declspec(align(16)) class torus : public Mesh
{
public:
	// Fix to align to 16 on heap so directX is happy.
	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}

	torus(ID3D11Device* device, const wchar_t* texfileName);

};

