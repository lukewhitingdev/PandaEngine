#include "GameObject.h"

void GameObject::Update(float deltaTime)
{
	if (_mesh && _transform) {
		// Calculate world matrix
		XMMATRIX scale = XMMatrixScaling(_transform->getScale().x, _transform->getScale().y, _transform->getScale().z);
		XMMATRIX rotation = XMMatrixRotationX(_transform->getRotation().x) * XMMatrixRotationY(_transform->getRotation().y) * XMMatrixRotationZ(_transform->getRotation().z);
		XMMATRIX translation = XMMatrixTranslation(_transform->getPosition().x, _transform->getPosition().y, _transform->getPosition().z);
		XMFLOAT4X4 worldMatrix;

		XMStoreFloat4x4(&worldMatrix, scale * rotation * translation);

		_transform->setWorldMatrix(worldMatrix);
		_mesh->setObjectMatrix(_transform->getWorldMatrix());

		_mesh->Update(deltaTime, _transform->getPosition(), _transform->getScale(), _transform->getYaw());
		_transform->updateMovement(deltaTime);


	}

	if (_rigidBody) {
		_rigidBody->move(deltaTime);
	}
}

void GameObject::Draw(ID3D11DeviceContext* context, ID3D11PixelShader* pixelShader, ID3D11VertexShader* vertexShader, ID3D11Buffer* constantBuffer, ConstantBuffer& cb)
{
	if(_mesh)
		_mesh->Draw(context, pixelShader, vertexShader, constantBuffer, cb);
}
