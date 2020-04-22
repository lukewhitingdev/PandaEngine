#pragma once
#include "Vector3D.h"


class ForceGenerator
{

public:
	ForceGenerator();
	static ForceGenerator* getInstance(); // Singleton Implementation.

	// Gravity and Drag.
	Vector3D generateGravityForce(float mass, float ammount);
	Vector3D generateLaminarDrag(Vector3D velocity, float dragFactor);
	Vector3D generateTurbulentDrag(Vector3D velocity, float dragFactor);

	// Springs.
	Vector3D generateAnchoredFakeSpringForce(Vector3D startObjectPos, Vector3D* anchorPos, float springConstant, float restLength, float damping, Vector3D velocity, float deltaTime, float mass);
	Vector3D generateConnectedSpringForce(Vector3D startObjectPos, Vector3D otherObjectPos, float springConstant, float restLength);
	Vector3D generateAnchoredSpringForce(Vector3D startObjectPos, Vector3D* anchorPos, float springConstant, float restLength);
	Vector3D generateConnectedBungieSpringForce(Vector3D startObjectsPos, Vector3D otherObjectPos, float springConstant, float restLength);
	Vector3D generateAnchoredBungieSpringForce(Vector3D startObjectPos, Vector3D* anchorPos, float springConstant, float restLength);


	// Buoyancy
	Vector3D generateBuoyancyForce(Vector3D objectPos, float maxDepth, float volume, float waterHeight, float liquidDensity);

	// Generic Forces

	Vector3D generateThrustForce(float mass, float ammount);
};

