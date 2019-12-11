#include "Mesh.h"

void Mesh::Draw(ID3D11DeviceContext* context, ID3D11PixelShader* pixelShader, ID3D11VertexShader* vertexShader, ID3D11Buffer* constantBuffer, ConstantBuffer& cb)
{
	// Transpose the local matrix and pass it to the constant buffer
	XMMATRIX world = XMLoadFloat4x4(&objectMatrix);
	cb.mWorld = XMMatrixTranspose(world);
	context->UpdateSubresource(constantBuffer, 0, nullptr, &cb, 0, 0);

	// Reset the pixel shader texture.
	context->PSSetShaderResources(0, 1, &textureResourceView);
	context->PSSetShader(pixelShader, nullptr, 0);

	// Set the vertex buffer
	context->VSSetShader(vertexShader, nullptr, 0);

	// Set buffers and draw.
	context->IASetVertexBuffers(0, 1, &objMeshLoader.VertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(objMeshLoader.IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	context->DrawIndexed(objMeshLoader.IndexCount, 0, 0);
}

void Mesh::Update(float time, bool rotate, bool translate)
{
	if (rotate) {
		XMStoreFloat4x4(&objectMatrix, XMMatrixRotationY(time) * XMMatrixScaling(scale.x, scale.y, scale.z));
	}
	if (translate) {
		XMStoreFloat4x4(&objectMatrix, XMMatrixTranslation(position.x, position.y, position.z) * XMMatrixScaling(scale.x, scale.y, scale.z));
	}

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

		deltaTime = deltaTime;

	}
}
