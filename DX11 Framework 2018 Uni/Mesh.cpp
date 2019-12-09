#include "Mesh.h"

void Mesh::Draw(ID3D11DeviceContext*, ID3D11PixelShader*, ID3D11Buffer*, ConstantBuffer&)
{
}

void Mesh::Update(float)
{
}

void Mesh::UpdateMovement(float deltaTime)
{
	lookDir.z = cos(yaw);
	lookDir.x = sin(yaw);


	// Only do this if we have control
	if (ObjectPossesed) {
		if (GetAsyncKeyState('W')) {
			speed = 0.01f;

			XMVECTOR vSpeed = XMVectorReplicate(speed);
			XMVECTOR vLook = XMLoadFloat3(&lookDir);
			XMVECTOR vPos = XMLoadFloat3(&position);

			vLook = XMVector3Normalize(vLook);

			XMStoreFloat3(&position, XMVectorMultiplyAdd(vSpeed, -vLook, vPos));
		}
		if (GetAsyncKeyState('S')) {
			speed = -0.01f;

			XMVECTOR vSpeed = XMVectorReplicate(speed);
			XMVECTOR vLook = XMLoadFloat3(&lookDir);
			XMVECTOR vPos = XMLoadFloat3(&position);

			vLook = XMVector3Normalize(vLook);

			XMStoreFloat3(&position, XMVectorMultiplyAdd(vSpeed, -vLook, vPos));
		}
		if (GetAsyncKeyState('A')) {
			yaw -= 0.001f;
			if (yaw >= 360.0f) {
				yaw = 0.0f;
			}
		}
		if (GetAsyncKeyState('D')) {
			yaw += 0.001;
			if (yaw >= 360.0f) {
				yaw = 0.0f;
			}
		}

	}
}
