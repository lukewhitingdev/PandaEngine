#pragma once
#include "Vector3D.h"



class playerController
{

public:
	playerController();

	void addToMovement(Vector3D force);
	void subtractFromMovement(Vector3D force);

	void setMovementVector(Vector3D value) { _movementVector = value; };
	Vector3D getMovementVector() { return _movementVector; };

private:
	Vector3D _movementVector;
};

