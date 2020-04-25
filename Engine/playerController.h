#pragma once
#include "Vector3D.h"



class playerController
{

public:
	playerController();

	void updateMovement(Vector3D force);

private:
	Vector3D movementVector;

};

