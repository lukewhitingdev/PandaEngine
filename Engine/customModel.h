#pragma once
#include "Mesh.h"
__declspec(align(16)) class customModel : public Mesh
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

	customModel(ID3D11Device* device, char* objfileName, bool rHand, meshType mType);
	customModel(ID3D11Device* device, const wchar_t* texfileName, char* objfileName, meshType mType);
	customModel(ID3D11Device* device, const wchar_t* texfileName, char* objfileName, bool rHand);

	virtual void Update(float time, XMFLOAT3 pos, XMFLOAT3 scale, float yaw);
};

