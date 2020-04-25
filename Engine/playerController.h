#pragma once
#include "Vector3D.h"



class playerController
{

public:
	playerController();

	void addToMovement(Vector3D force);
	void subtractFromMovement(Vector3D force);

	Vector3D getMovementVector() { return _movementVector; };

private:
	Vector3D _movementVector;

};

