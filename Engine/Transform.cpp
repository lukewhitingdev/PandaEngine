#include "Transform.h"

Transform::Transform()
{
	_previousVelocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_previousPosition = XMFLOAT3(0.0f, 0.0f, 0.0f); 
	_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_scale = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_world = XMFLOAT4X4();
	_centreOfMass = Vector3D(0.0f, 0.0f, 0.0f);
	_quaternionRotation = XMMATRIX();
	_usingQuaternionRotation = false;


}

void Transform::Update(float deltaTime)
{
	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(getScale().x, getScale().y, getScale().z);
	XMMATRIX rotation = XMMatrixRotationX(getRotation().x) * XMMatrixRotationY(getRotation().y) * XMMatrixRotationZ(getRotation().z);
	XMMATRIX translation = XMMatrixTranslation(getPosition().x, getPosition().y, getPosition().z);

	if (_usingQuaternionRotation) {
		XMStoreFloat4x4(&_world, scale * _quaternionRotation * translation);
	}
	else {
		XMStoreFloat4x4(&_world, scale * rotation * translation);
	}


	//updateMovement(deltaTime);
}

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