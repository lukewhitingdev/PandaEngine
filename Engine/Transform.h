#include <DirectXMath.h>
#include <d3d11_1.h>
#include "Vector3D.h"
using namespace DirectX;

#pragma once
class Transform
{
public:

	Transform();

	void Update(float deltaTime);

	XMFLOAT3 getPrevVelocity() { return _previousVelocity; };
	XMFLOAT3 getPrevPosition() { return _previousPosition; };
	XMFLOAT3 getPosition() { return _position; };
	Vector3D getVector3Position() { return Vector3D(_position.x, _position.y, _position.z); };
	XMFLOAT3 getRotation() { return _rotation; };
	XMFLOAT3 getScale() { return _scale; };
	XMMATRIX getWorldMatrix() { return XMLoadFloat4x4(&_world); };
	Vector3D getCenterOfMass() { return _centreOfMass; };

	void setQuaternionRotation(XMMATRIX value) { _quaternionRotation = value; setUsingQuaternionRotation(true); };	// Used to set the transform Update() to use the quaternion rotator rather than euler angles.
	void setUsingQuaternionRotation(bool value) { _usingQuaternionRotation = value; };								// Used in-class to allow the update to use the quat instead of the euler angles. Should not be used explicitly unless a quaternion has been defined previously.
	void setPrevVelocity(XMFLOAT3 value) { _previousVelocity = value; };
	void setPrevPosition(XMFLOAT3 value) { _previousPosition = value; };
	void setPosition(XMFLOAT3 value) { _position = value; setPrevPosition(_position); };
	void setRotation(XMFLOAT3 value) { _rotation = value; };
	void setScale(XMFLOAT3 value) { _scale = value; };
	void setScale(float value) { _scale = XMFLOAT3(value, value, value); };
	void setWorldMatrix(XMFLOAT4X4 value) { _world = value; };
	void setWorldMatrix(XMMATRIX value) { XMStoreFloat4x4(&_world, value); };
	void setCenterOfMass(Vector3D value) { _centreOfMass = value; };

	// Need to be depricated.

	float getYaw() { return _yaw; };
	void setYaw(float value) { _yaw = value; };

						/* Movement Commands */

	void setCanMove(bool value) { _canMove = value; };

protected:
	void updateMovement(float deltaTime);

private:
	XMFLOAT3 _previousVelocity;
	XMFLOAT3 _previousPosition;
	XMFLOAT3 _position;
	XMFLOAT3 _rotation;
	XMFLOAT3 _scale;
	XMFLOAT4X4 _world;
	Vector3D _centreOfMass;
	XMMATRIX _quaternionRotation;

	bool _usingQuaternionRotation;


	// Movement
	bool _canMove = false;
	XMFLOAT3 _lookDir = { 0.0f, 0.0f, 0.0f };
	float _speed = 0.000001f;
	float _acceleration = 0.0000005f;
	float _yaw = 0;
	float _pitch = 0;
	float _roll = 0;
};

