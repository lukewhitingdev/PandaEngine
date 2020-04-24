#include "RigidBody.h"

RigidBody::RigidBody(Transform* transform)
{
	_forceGenerator = _forceGenerator->getInstance();	// Singleton.
	_transform = transform;
	_sphereCollider = nullptr;							// null until a collider is assigned.
	damping = 0.5f;
	position = transform->getVector3Position();
	setMass(1.0f);										// Default value to allow for missed implementation when creating objects.
}

void RigidBody::setCollisionSphere(sphereCollider* collider)
{
	_sphereCollider = collider;
}

// Old dont use anymore....
void RigidBody::integrate(float deltaTime)
{
	assert(deltaTime > 0.0f);


	_transform->setPrevVelocity(velocity);

	// Update linear position.									// Position = Position + Velocity * deltaTime.
	position.addScaledVector(velocity, deltaTime);				// ut

	// Work out acceleration.									// Acceleration = combinedForce * inverseMass (so basically combinedForce / inverseMass)
	acceleration.addScaledVector(combinedForce, inverseMass);

	// Velocity = Velocity + acceleration * deltaTime.
	velocity.addScaledVector(acceleration, deltaTime);			// v = at (v = u + at)

	velocity *= powf(damping, deltaTime);						// Applying damping.

	if (_sphereCollider)
		updateColliderPosition(position);

	_transform->setPosition(position);

	clearCombinedForce();
}

void RigidBody::move(float deltaTime)
{

	_transform->setPrevVelocity(velocity);

	// Update accel.
	acceleration = combinedForce * inverseMass;  // Accel = force / mass.

	Vector3D movedPosition;
	movedPosition = Vector3D::fromXMFLOAT3(_transform->getPrevPosition()) + Vector3D::fromXMFLOAT3(_transform->getPrevVelocity()) * deltaTime + acceleration * 0.5f * deltaTime * deltaTime;

	velocity = Vector3D::fromXMFLOAT3(_transform->getPrevVelocity()) + acceleration * deltaTime;

	velocity *= powf(damping, deltaTime);

	_transform->setPosition(movedPosition);

	if (_sphereCollider)
		updateColliderPosition(movedPosition);

	clearCombinedForce();

}
