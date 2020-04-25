#pragma once
#include "Mesh.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Debug.h"
#include "Collision.h"
#include "inputManager.h"
#include "playerController.h"

class GameObject
{

public:

	GameObject() {};
	GameObject(Transform* transform) { _transform = transform;};
	GameObject(Transform* transform, Mesh* mesh) { _transform = transform; _mesh = mesh; };
	
	// Used to update the GameObject and its components.
	void Update(float deltaTime);

	// Used to draw the GameObject's mesh and other visual components.
	void Draw(ID3D11DeviceContext* context, ID3D11PixelShader* pixelShader, ID3D11VertexShader* vertexShader, ID3D11Buffer* constantBuffer, ConstantBuffer& cb);

	void updateCollisions(GameObject* object1, GameObject* object2);

				/* Getters and Setters */

	// Used to change or in the current GameObject's mesh.
	void changeMeshComponent(Mesh mesh) { _mesh = &mesh; };
	void changeTransformComponent(Transform transform) { _transform = &transform; };

	// Used to add a rigidBody to the current GameObject (REQUIRES TRANSFORM);
	void addRigidBody() { _rigidBody = new RigidBody(_transform); };
	
	// Used to add a input manager to the current GameObject.
	void addInputManager() { _inputManager = inputManager::getInstance(); };

	// Used to add a player controller to the current GameObject.
	void addPlayerController() { _playerController = new playerController(); };

	// Used to remove Rigidbody from a GameObject, (WILL DISABLE COLLISIONS AS PHYSICS IS NEEDED FOR RESOLUTION)
	void removeRigidBody() { _rigidBody = nullptr; };
	
	// Used to remove movement controls from the object.
	void makeGameObjectStatic(bool value) { isStaticObject = value; };
	bool getIsGameObjectStatis() { return isStaticObject; };

	Mesh* getMeshComponent() { return _mesh; };
	Transform* getTransformComponent() { return _transform; };
	RigidBody* getRigidbodyComponent() { return _rigidBody; };

private:

	bool isStaticObject = false;

										/* Components. */
	Mesh* _mesh = nullptr;								// Handles Appearance and Mesh generation (REQUIRES A TRANSFORM).
	Transform* _transform = nullptr;					// Handles position in world space and scale of the GameObject.
	RigidBody* _rigidBody = nullptr;					// Handles physics and collision between physics objects.
	Collision* _collision = nullptr;					// Handles collisions once physics are enabled (REQUIRES A RIGIDBODY).
	inputManager* _inputManager = nullptr;				// Handles keypresses and general input from the player (SINGLETON).
	playerController* _playerController = nullptr;		// Handles player movement mainly for demo purposes (REQUIRES A RIGIDBODY).

	// Debug
	bool physDebug = true;								// Hard coded value to allow physics to skip the 60fps cap when debugging.
};

