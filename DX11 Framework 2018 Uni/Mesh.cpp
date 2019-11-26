#include "Mesh.h"

void Mesh::Draw(ID3D11DeviceContext*, ID3D11PixelShader*, ID3D11Buffer*, ConstantBuffer&)
{
}

void Mesh::Update(float)
{
}

void Mesh::UpdateMovement()
{
	// Only do this if we have control
	if (ObjectPossesed) {
		if (GetAsyncKeyState('W')) {
			position.z -= 0.01f;
		}
		if (GetAsyncKeyState('S')) {
			position.z += 0.01f;
		}
		if (GetAsyncKeyState('A')) {
			yaw -= 0.001f;
		}
		if (GetAsyncKeyState('D')) {
			yaw += 0.001;
		}
	}
}
