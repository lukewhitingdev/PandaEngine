#include "GameObject.h"

void GameObject::Update(float deltaTime)
{
	if (_mesh && _transform) {

		// Set world matrix to align with transform.
		_mesh->setObjectMatrix(_transform->getWorldMatrix());

		// Update
		_transform->Update(deltaTime);
	}

	if (_rigidBody) {
		if (deltaTime < 0.016f) {																	// Quick fix so that if the game lags below 60fps the physics dont die.
			ForceGenerator* forceGen = ForceGenerator::getInstance();								// Get the singleton instance of the force generator.
			if (_rigidBody->getCanPhysMove()) {														// If we can move then allow keyboard inputs.
				Vector3D movementForce = Vector3D();
				float force = 10.0f;

				if (getKeyDown('A'))
				{
					movementForce.x -= force;
				}
				if (getKeyDown('D'))
				{
					movementForce.x += force;
				}
				if (getKeyDown('W'))
				{
					movementForce.z += force;
				}
				if (getKeyDown('S'))
				{
					movementForce.z -= force;
				}

				if (getKeyDown('F')) {
					movementForce.y += force;
				}

				_rigidBody->addForce(movementForce);
			}

			if (_transform->getPosition().y > 1.5f)
				_rigidBody->addForce(forceGen->generateGravityForce(_rigidBody->getMass(), 1.0f));			// Gravity

			if (_transform->getPosition().y < 1.5f)
				_transform->setPosition(XMFLOAT3(_transform->getPosition().x, 1.25f, _transform->getPosition().z));

			_rigidBody->addForce(forceGen->generateLaminarDrag(_rigidBody->velocity, 1.0f));			// Laminar Drag

			// Update
			_rigidBody->move(deltaTime);

			Debug::DebugToOutput(_transform->getPosition().y);
		}
	}
}

void GameObject::Draw(ID3D11DeviceContext* context, ID3D11PixelShader* pixelShader, ID3D11VertexShader* vertexShader, ID3D11Buffer* constantBuffer, ConstantBuffer& cb)
{
	if(_mesh)
		_mesh->Draw(context, pixelShader, vertexShader, constantBuffer, cb);
}

#pragma region Functions for key presses

// Allows the user to get one output for the duration the key is pressed.
bool GameObject::getKey(char key)
{
	if (getKeyDown(key)) {
		// If we are not holding a key already.
		if (keyPressed == false) {
			keyPressed = true;
			return true;
		}
		else {
			return false;
		}
	}
	if (getKeyUp(key)) {
		keyPressed = false;
		return false;
	}
}

bool GameObject::getKeyDown(char key)
{
	if (GetKeyState(key) & 0x8000) {
		return true;
	}
	else {
		return false;
	}
}

bool GameObject::getKeyUp(char key)
{
	if (GetKeyState(key) & 0x8000) {
		return false;
	}
	else {
		return true;
	}
}

#pragma endregion
