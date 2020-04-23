#pragma once
#include "Mesh.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Debug.h"

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

				/* Getters and Setters */

	// Used to change or in the current GameObject's mesh.
	void changeMeshComponent(Mesh mesh) { _mesh = &mesh; };
	void changeTransformComponent(Transform transform) { _transform = &transform; };

	// Used to add a rigidBody to the current GameObject (REQUIRES TRANSFORM);
	void addRigidBody() { _rigidBody = new RigidBody(_transform); };
	void removeRigidBody() { _rigidBody = nullptr; };

	Mesh* getMeshComponent() { return _mesh; };
	Transform* getTransformComponent() { return _transform; };
	RigidBody* getRigidbodyComponent() { return _rigidBody; };

private:

	bool keyPressed = false;
	bool getKey(char key);
	bool getKeyDown(char key);
	bool getKeyUp(char key);


	Mesh* _mesh = nullptr;								// Handles Appearance and Mesh generation (REQUIRES A TRANSFORM).
	Transform* _transform = nullptr;					// Handles position in world space and scale of the GameObject.
	RigidBody* _rigidBody = nullptr;					// Handles physics and collision between physics objects.
};

