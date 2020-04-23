#include "Transform.h"
#include "Vector3D.h"
#include "sphereCollider.h"
#include "ForceGenerator.h"

#pragma once
class RigidBody
{


public:

	RigidBody(Transform* transform);

	void setInverseMass(float value) { inverseMass = value; };
	void setMass(float value) { inverseMass = 1 / value; };
	float getMass() { return inverseMass; };
	void setVelocity(Vector3D value) { velocity = value; };

	// Collision
	void setCollisionSphere(sphereCollider* collider);						// Might want to change this to accept any collider later.
	void updateColliderPosition(Vector3D pos) { _sphereCollider->setColliderPosition(pos); };

	void integrate(float deltaTime);
	void move(float deltaTime);

	void addForce(const Vector3D& force) { combinedForce += force; };
	void clearCombinedForce() { combinedForce.clear(); };

	void setCanPhysMove(bool value) { canPhysMove = value; };
	bool getCanPhysMove() { return canPhysMove; };

	Vector3D combinedForce;				// Combined vector of all forces.
	Vector3D position;					// Position of the particle in world space.
	Vector3D velocity;					// Velocity of the particle in world space.
	Vector3D acceleration;				// Acceleration of the particle in world space.
	float damping;						// Ammount of damping applied to linear motion.

	Transform* _transform;				// Used to get the position of the object.
	ForceGenerator* _forceGenerator;	// Used to generate forces to be added together.
	sphereCollider* _sphereCollider;	// Used to find collisions between two objects.

protected:

	float inverseMass;		// 1/mass used to calculate acceleration, inversed to simplify defining infinite mass objects and avoiding zero mass ones.
	bool canPhysMove = false;			// Used to control whether the physics object can move or not.


};

