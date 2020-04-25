#include "playerController.h"

playerController::playerController()
{
	movementVector = Vector3D();
}

void playerController::updateMovement(Vector3D force)
{
	movementVector += force;
}
