#pragma once
#include "Vector3D.h"
class sphereCollider
{

public:
	sphereCollider(Vector3D pos, float radius);

	void setColliderPosition(Vector3D value) { _position = value; };
	void setColliderRadius(float value) { _radius = value; };

	Vector3D getColliderPosition() { return _position; }
	float getColliderRadius() { return _radius; }

private:
	Vector3D _position;
	float _radius;
};

