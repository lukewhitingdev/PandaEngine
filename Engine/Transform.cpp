#include "Transform.h"

void Transform::updateMovement(float deltaTime) {

	// -------------------------- UPDATE TO NEW PHYSICS BASED SYSTEM ----------------------------- //

	_lookDir.z = cos(_yaw);
	_lookDir.x = sin(_yaw);

	// Only do this if we have control
	if (_canMove) {
		if (GetAsyncKeyState('W')) {
			_speed = 0.01f;

			XMVECTOR vSpeed = XMVectorReplicate(_speed);
			XMVECTOR vLook = XMLoadFloat3(&_lookDir);
			XMVECTOR vPos = XMLoadFloat3(&_position);

			vLook = XMVector3Normalize(vLook);

			XMStoreFloat3(&_position, XMVectorMultiplyAdd(vSpeed, -vLook, vPos));
		}
		if (GetAsyncKeyState('S')) {
			_speed = -0.01f;

			XMVECTOR vSpeed = XMVectorReplicate(_speed);
			XMVECTOR vLook = XMLoadFloat3(&_lookDir);
			XMVECTOR vPos = XMLoadFloat3(&_position);

			vLook = XMVector3Normalize(vLook);

			XMStoreFloat3(&_position, XMVectorMultiplyAdd(vSpeed, -vLook, vPos));
		}
		if (GetAsyncKeyState('A')) {
			_yaw -= 0.001f;
			if (_yaw >= 360.0f) {
				_yaw = 0.0f;
			}
		}
		if (GetAsyncKeyState('D')) {
			_yaw += 0.001;
			if (_yaw >= 360.0f) {
				_yaw = 0.0f;
			}
		}

		deltaTime = deltaTime;

	}
}