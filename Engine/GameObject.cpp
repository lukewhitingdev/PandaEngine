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
			float fixedDeltaTime = 0.016f;															// Fixes the deltaTime to 60fps to allow the physics to run nicer.

			ForceGenerator* forceGen = ForceGenerator::getInstance();								// Get the singleton instance of the force generator.
			if (_rigidBody->getCanPhysMove() && isStaticObject == false) {							// If we can move then allow keyboard inputs.
				static Vector3D* movementForce = nullptr;
				if (movementForce != nullptr) {
				

					float force = 0.2f * _rigidBody->getMass();

					if (getKeyDown('A'))
					{
						movementForce->x -= force;
					}
					if (getKeyDown('D'))
					{
						movementForce->x += force;
					}
					if (getKeyDown('W'))
					{
						movementForce->z += force;
					}
					if (getKeyDown('S'))
					{
						movementForce->z -= force;
					}

					if (getKeyDown('F')) {
						_rigidBody->addForce(forceGen->generateAnchoredBungieSpringForce(_transform->getVector3Position(), new Vector3D(0, 10, 0), 1.0f, 1.0f));
					}

					if (getKeyDown('G')) {
						//_rigidBody->addForce(forceGen->generateAnchoredSpringForce(_transform->getVector3Position(), new Vector3D(-5, 5, 0), 1.0f, 1.0f));

						// Fix this maybe later something funny going on here??
						Vector3D force = forceGen->generateBuoyancyForce(_transform->getVector3Position(), 4.0f, 10.0f, 2.0f, 1.0f);
						force.invert();
						_rigidBody->addForce(force);
					}


					Debug::DebugToOutput(movementForce->x);
					Debug::DebugToOutput(movementForce->y);
					Debug::DebugToOutput(movementForce->z);

					_rigidBody->addForce(*movementForce);
				}
			}

			if(_transform->getPosition().y > 1.5f)
				_rigidBody->addForce(forceGen->generateGravityForce(_rigidBody->getMass(), 1.0f));					// Apply gravity if not a ground level to prevent jittering.
				
			if (_transform->getPosition().y < 1.5f)
				_transform->setPosition(XMFLOAT3(_transform->getPosition().x, 1.25f, _transform->getPosition().z));	// Make sure that if the gravity pushes too hard between frames it resets. 

			_rigidBody->addForce(forceGen->generateLaminarDrag(_rigidBody->velocity, 1.0f));						// Laminar Drag


			_rigidBody->move(fixedDeltaTime);																		// Update
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
