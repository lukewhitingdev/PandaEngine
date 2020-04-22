#include "GameObject.h"

void GameObject::Update(float deltaTime)
{
	if(_mesh)
		_mesh->Update(deltaTime);
}

void GameObject::Draw(ID3D11DeviceContext* context, ID3D11PixelShader* pixelShader, ID3D11VertexShader* vertexShader, ID3D11Buffer* constantBuffer, ConstantBuffer& cb)
{
	if(_mesh)
		_mesh->Draw(context, pixelShader, vertexShader, constantBuffer, cb);
}
