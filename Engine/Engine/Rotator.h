#pragma once
#include "Vector3D.h"
#include "Quaternion.h"
#include "Debug.h"

__declspec(align(16)) class Rotator
{

public:

	// Fix to align to 16 on heap so directX is happy.
	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}

	Rotator(float mass, float radius);

	Vector3D generateTorgueVector(Vector3D force, Vector3D point);
	Vector3D generateAngularAcceleration();
	Vector3D generateAngularVelocity(float deltaTime);
	XMMATRIX updateOrientation(float deltaTime);

	XMMATRIX updateRotation(float deltaTime);

private:
	XMMATRIX InertiaTensor;
	XMMATRIX inverseInertiaTensor;
	Vector3D torque;
	Vector3D angularVelocity;
	Vector3D angularAcceleration;
	Vector3D position;
	Quaternion orientation;
	float angularDamping;		// Higher the value the more it'll spin
	float _mass;
	float _radius;
};

