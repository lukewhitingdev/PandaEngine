#include "Rotator.h"

Rotator::Rotator(float mass, float radius)
{
	_mass = mass;
	_radius = radius;
	orientation = Quaternion();
	torque = Vector3D(0, 0, 0);

	XMFLOAT3X3 tensor = XMFLOAT3X3(0.4f * (_mass * _radius * _radius), 0.0f, 0.0f,
		0.0f, 0.4f * (_mass * _radius * _radius), 0.0f,
		0.0f, 0.0f, 0.4f * (_mass * _radius * _radius));

	XMFLOAT3X3 InverseTensor = XMFLOAT3X3(-0.4f * (_mass * _radius * _radius), 0.0f, 0.0f,
		0.0f, -0.4f * (_mass * _radius * _radius), 0.0f,
		0.0f, 0.0f, -0.4f * (_mass * _radius * _radius));

	InertiaTensor = XMLoadFloat3x3(&tensor);
	inverseInertiaTensor = XMLoadFloat3x3(&InverseTensor);

	angularDamping = 0.01f;

}

Vector3D Rotator::generateTorgueVector(Vector3D force, Vector3D point)
{
	//angularAcceleration = Vector3D(0, 0, 0);
	//angularVelocity = Vector3D(0, 0, 0);

	Vector3D returnForce = point.cross(force);
	torque += returnForce;

	return returnForce;
}

Vector3D Rotator::generateAngularAcceleration()
{
	XMVECTOR test = XMVector3Transform(torque, inverseInertiaTensor);
	Vector3D force = Vector3D(0, 0, 0);

	return force.fromXMVECTOR(test);
}

Vector3D Rotator::generateAngularVelocity(float deltaTime)
{
	// Generate Generic Angular Velocity
	Vector3D force = Vector3D(0, 0, 0);
	force = angularVelocity + angularAcceleration * deltaTime;

	// Add Damping
	force *= pow(angularDamping, deltaTime);

	return force;
}

XMMATRIX Rotator::updateOrientation(float deltaTime)
{
	XMMATRIX outcome = XMMATRIX();
	orientation.addScaledVector(angularVelocity, deltaTime);

	orientation.normalise();

	CalculateTransformMatrixRowMajor(outcome, position, orientation);

	return outcome;
}

XMMATRIX Rotator::updateRotation(float deltaTime)
{
	angularAcceleration = generateAngularAcceleration();
	angularVelocity = generateAngularVelocity(deltaTime);

	return updateOrientation(deltaTime);
}

