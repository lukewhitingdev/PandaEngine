#include "Collision.h"


bool Collision::checkCollision(sphereCollider* collider1, sphereCollider* collider2)
{
	if (collider1 && collider2) {																	// Check if both the objects have colliders.

		//Debug::DebugToOutput(collider1->getColliderPosition().x - collider2->getColliderPosition().x);

		Vector3D localCollider = collider1->getColliderPosition();
		Vector3D extCollider = collider2->getColliderPosition();

		float xDist = localCollider.x - extCollider.x;
		float yDist = localCollider.y - extCollider.y;
		float zDist = localCollider.z - extCollider.z;

		float dist = sqrt(
		(xDist * xDist) +
		(yDist * yDist) +
		(zDist * zDist)
			);

		//Debug::DebugToOutput(dist);

		float radSum = collider1->getColliderRadius() + collider2->getColliderRadius();

		if (dist <= radSum) {
			return true;																					// if the distance intrudes on the bounds of the sphere collider a collision has occured.
		}

		return false;																					   // if the distance is outside the bounds dont do anything.
	}
	return false;
}

void Collision::resolveCollision(RigidBody* particle1, RigidBody* particle2)
{

	particle1->_transform->setPosition(particle1->_transform->getPrevPosition());
	particle2->_transform->setPosition(particle2->_transform->getPrevPosition());

	Vector3D dist = particle1->_transform->getVector3Position() - particle2->_transform->getVector3Position();
	Vector3D pos = particle1->_transform->getVector3Position();
	Vector3D incPos = particle2->_transform->getVector3Position();
	Vector3D invDist = dist;
	invDist.invert();

	Vector3D relativeVelocity = particle1->velocity - particle2->velocity;

	if ((relativeVelocity + dist) >= 0) {
		float e = 1.0f;

		Vector3D Ua = Vector3D::fromXMFLOAT3(particle1->_transform->getPrevVelocity());
		Vector3D Ub = Vector3D::fromXMFLOAT3(particle2->_transform->getPrevVelocity());

		float Ma = particle1->getMass();
		float Mb = particle2->getMass();

		Vector3D finalVelo1 = Ua * Ma + Ub * Mb + (Ub - Ua) * e * Mb;
		finalVelo1 = finalVelo1 / (Ma + Mb);

		Vector3D finalVelo2 = Ua * Ma + Ub * Mb + (Ua - Ub) * e * Mb;
		finalVelo2 = finalVelo2 / (Ma + Mb);

		finalVelo1 = (finalVelo1 * dist.norm());
		finalVelo2 = (finalVelo2 * invDist.norm());

		particle1->setVelocity(finalVelo1);
		particle2->setVelocity(finalVelo2);

		Debug::DebugToOutput("VeloX: ", finalVelo1.x);
		Debug::DebugToOutput("VeloY: ", finalVelo1.y);
		Debug::DebugToOutput("VeloZ: ", finalVelo1.z);
	}
}