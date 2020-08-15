#include "ForceGenerator.h"


ForceGenerator::ForceGenerator()
{

}

ForceGenerator* ForceGenerator::getInstance()
{
	static ForceGenerator* instance;
	if (!instance) {
		instance = new ForceGenerator();
		return instance;
	}
	return instance;
}

Vector3D ForceGenerator::generateGravityForce(float mass, float ammount)
{
	Vector3D force = Vector3D(0, 0, 0);
	force.y = -ammount * mass;
	return force;
}

Vector3D ForceGenerator::generateLaminarDrag(Vector3D velocity, float dragFactor)
{
	Vector3D force = Vector3D(0, 0, 0);

	force.x = -dragFactor * velocity.x;
	force.y = -dragFactor * velocity.y;
	force.z = -dragFactor * velocity.z;

	return force;

}

Vector3D ForceGenerator::generateTurbulentDrag(Vector3D velocity, float dragFactor)
{
	Vector3D force = Vector3D(0, 0, 0);

	float VeloMag = velocity.magnitude(); // How to get the magnitude from when a negative velo??? 
	Vector3D unitVelo = velocity.norm();

	float dragMag = dragFactor * VeloMag * VeloMag;

	force.x = -dragMag * unitVelo.x;
	force.y = -dragMag * unitVelo.y;
	force.z = -dragMag * unitVelo.z;

	return force;
}

Vector3D ForceGenerator::generateAnchoredFakeSpringForce(Vector3D startObjectPos, Vector3D* anchorPos, float springConstant, float restLength, float damping, Vector3D velocity, float deltaTime, float mass)
{
	// Position relative to anchor.
	Vector3D position = startObjectPos;
	position -= *anchorPos;

	// Calculate constants and check whether in bounds.
	float gamma = 0.5f * sqrt(4 * springConstant - damping * damping);
	if (gamma == 0.0f)
		return Vector3D(0, 0, 0);

	Vector3D c = position * (damping / (2.0f * gamma)) + velocity * (1.0f / gamma);

	Vector3D target = position * cosf(gamma * deltaTime) + c * sinf(gamma * deltaTime);

	target *= expf(-0.5f * deltaTime * damping);

	// Calculate the resulting accel and force.

	Vector3D acceleration = (target - position) * (1.0f / deltaTime * deltaTime) - velocity * deltaTime;

	Vector3D force = acceleration * mass;

	return force;

}


Vector3D ForceGenerator::generateConnectedSpringForce(Vector3D startObjectPos, Vector3D otherObjectPos, float springConstant, float restLength)
{
	Vector3D force = Vector3D(0, 0, 0);

	force = startObjectPos;
	force -= otherObjectPos;

	// Calculate the magniture of the force.
	float magnitude = force.magnitude();
	magnitude = fabsf(magnitude - restLength);
	magnitude *= springConstant;

	// Calculate the final force and apply it.
	force.norm();
	force *= -magnitude;

	return force;
}

Vector3D ForceGenerator::generateAnchoredSpringForce(Vector3D startObjectPos, Vector3D* anchorPos, float springConstant, float restLength)
{
	// Calculate the vector of the spring.
	Vector3D force = Vector3D(0, 0, 0);
	force = startObjectPos;
	force -= *anchorPos;

	// Calculate the magniture of the force.
	float magnitude = force.magnitude();
	magnitude = fabsf(magnitude - restLength);
	magnitude *= springConstant;

	// Calculate the final force and apply it.
	force.norm();
	force *= -magnitude;

	return force;
}

Vector3D ForceGenerator::generateConnectedBungieSpringForce(Vector3D startObjectPos, Vector3D otherObjectPos, float springConstant, float restLength)
{
	Vector3D force = Vector3D(0, 0, 0);
	force = startObjectPos;
	force -= otherObjectPos;

	float magnitude = force.magnitude();

	// Do nothing if the spring is contracted close.
	if (magnitude <= restLength)
		return Vector3D(0, 0, 0);

	magnitude = springConstant * (restLength - magnitude);

	// Calculate final force.
	force.norm();
	force *= -magnitude;

	return force;
}

Vector3D ForceGenerator::generateAnchoredBungieSpringForce(Vector3D startObjectPos, Vector3D* anchorPos, float springConstant, float restLength)
{
	Vector3D force = Vector3D(0, 0, 0);
	force = startObjectPos;
	force -= *anchorPos;

	float magnitude = force.magnitude();

	// Do nothing if the spring is contracted close.
	if (magnitude <= restLength)
		return Vector3D(0, 0, 0);

	magnitude = springConstant * (restLength - magnitude);

	// Calculate final force.
	force.norm();
	force *= magnitude;

	return force;
}

Vector3D ForceGenerator::generateBuoyancyForce(Vector3D objectPos, float maxDepth, float volume, float waterHeight, float liquidDensity)
{
	Vector3D force = Vector3D(0, 0, 0);

	// Current Submersion Depth.
	float depth = objectPos.y;

	// See if we are in the water or not.
	if (depth >= waterHeight + maxDepth)
		return Vector3D(0, 0, 0);			// If we are just dont do anything.

	// Check to see if we are at maxDepth (Fully Submerged)
	if (depth <= waterHeight - maxDepth) {
		force.y = liquidDensity * volume;  // If we are then just apply a constant force since
		return force;					   // we are not displacing any more water.
	}

	// Otherwise we are partially Submerged.
	force.y = liquidDensity * volume * (depth - maxDepth - waterHeight) / 2 * maxDepth;

	return force;
}

Vector3D ForceGenerator::generateThrustForce(float mass, float ammount)
{
	Vector3D force = Vector3D(0, 0, 0);
	force.y = ammount * mass;
	return force;
}
