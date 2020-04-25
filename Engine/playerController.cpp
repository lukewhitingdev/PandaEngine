#include "playerController.h"

playerController::playerController()
{
	_movementVector = Vector3D();
}

void playerController::addToMovement(Vector3D force)
{
	_movementVector += force;
}

void playerController::subtractFromMovement(Vector3D force)
{
	_movementVector -= force;
}
