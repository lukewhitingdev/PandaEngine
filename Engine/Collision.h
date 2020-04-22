#pragma once
#include "sphereCollider.h"
#include "RigidBody.h"

class Collision
{
public:
	bool checkCollision(sphereCollider* collider1, sphereCollider* collider2);

	void resolveCollision(RigidBody* particle1, RigidBody* particle2);

};

