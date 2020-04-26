#include "GameObject.h"

void GameObject::Update(float deltaTime)
{
	if (_mesh && _transform) {

		// Set world matrix to align with transform.
		_mesh->setObjectMatrix(_transform->getWorldMatrix());

		// Update
		_transform->Update(deltaTime);
	}

	if (_rotator) {
		_transform->setQuaternionRotation(_rotator->updateRotation(deltaTime));
	}

	if (_rigidBody) {
		if (deltaTime < 0.016f || physDebug) {														// Quick fix so that if the game lags below 60fps the physics dont die.
			float fixedDeltaTime = 0.016f;															// Fixes the deltaTime to 60fps to allow the physics to run nicer.

			ForceGenerator* forceGen = ForceGenerator::getInstance();								// Get the singleton instance of the force generator.

			if (_rigidBody->getCanPhysMove() && isStaticObject == false) {							// If we can move then allow keyboard inputs.

				_playerController->setMovementVector(Vector3D());
				float force = 1.0f;

				if (_inputManager->getKeyDown('A'))
				{
					_playerController->subtractFromMovement(Vector3D(force, 0, 0));
					_rigidBody->addForce(_playerController->getMovementVector());
				}
				if (_inputManager->getKeyDown('D'))
				{
					_playerController->addToMovement(Vector3D(force, 0, 0));
					_rigidBody->addForce(_playerController->getMovementVector());
				}
				if (_inputManager->getKeyDown('W'))
				{
					_playerController->addToMovement(Vector3D(0, 0, force));
					_rigidBody->addForce(_playerController->getMovementVector());
				}
				if (_inputManager->getKeyDown('S'))
				{
					_playerController->subtractFromMovement(Vector3D(0, 0, force));
					_rigidBody->addForce(_playerController->getMovementVector());
				}

				if (_inputManager->getKeyDown('F')) {
					_rigidBody->addForce(forceGen->generateAnchoredBungieSpringForce(_transform->getVector3Position(), new Vector3D(0, 10, 0), 1.0f, 1.0f));
				}

				if (_inputManager->getKeyDown('G')) {
					//_rigidBody->addForce(forceGen->generateAnchoredSpringForce(_transform->getVector3Position(), new Vector3D(-5, 5, 0), 1.0f, 1.0f));

					// Fix this maybe later something funny going on here??
					Vector3D force = forceGen->generateBuoyancyForce(_transform->getVector3Position(),
																							2.0f,										// Depth
																							10.0f,										// Volume
																							2.0f,										// Water Height
																							1.0f										// Liquid Density
						);

					force.invert();
					_rigidBody->addForce(force);
				}
			}

			if(_transform->getPosition().y > 1.5f)
				_rigidBody->addForce(forceGen->generateGravityForce(_rigidBody->getMass(), 1.0f));					// Apply gravity if not a ground level to prevent jittering.
			

			if (_transform->getPosition().y < 1.5f)
				_transform->setPosition(XMFLOAT3(_transform->getPosition().x, 1.25f, _transform->getPosition().z));	// Make sure that if the gravity pushes too hard between frames it resets. 

			_rigidBody->addForce(forceGen->generateLaminarDrag(_rigidBody->velocity, 1.0f));						// Laminar Drag


			_rigidBody->move(fixedDeltaTime);																		// Update
		}

		if (_rotator) {
			if (_inputManager->getKeyDown('T'))
				_rotator->generateTorgueVector(Vector3D(0.5f, 0.0f, 0.0f), Vector3D(0, 0.25f, 0.0f));

			if (_inputManager->getKeyDown('Y'))
				_rotator->generateTorgueVector(Vector3D(-0.5f, 0.0f, 0.0f), Vector3D(0.0f, 0.25f, 0.0f));
		}
	}

}

void GameObject::Draw(ID3D11DeviceContext* context, ID3D11PixelShader* pixelShader, ID3D11VertexShader* vertexShader, ID3D11Buffer* constantBuffer, ConstantBuffer& cb)
{
	if(_mesh)
		_mesh->Draw(context, pixelShader, vertexShader, constantBuffer, cb);
}

void GameObject::updateCollisions(GameObject* object1, GameObject* object2)
{

	sphereCollider* collider1 = nullptr;
	sphereCollider* collider2 = nullptr;

	RigidBody* rigidBody1 = nullptr;
	RigidBody* rigidBody2 = nullptr;

	if (object1->getRigidbodyComponent() != nullptr) {
		rigidBody1 = object1->getRigidbodyComponent();
		collider1 = object1->getRigidbodyComponent()->_sphereCollider;
	}

	if (object2->getRigidbodyComponent() != nullptr) {
		rigidBody2 = object2->getRigidbodyComponent();
		collider2 = object2->getRigidbodyComponent()->_sphereCollider;
	}

	if (collider1 != nullptr && collider2 != nullptr) {
		if (_collision->checkCollision(collider1, collider2)) {
			_collision->resolveCollision(rigidBody1, rigidBody2);
		}
	}
}
