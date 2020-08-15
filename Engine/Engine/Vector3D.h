#pragma once
#include <iostream>
#include <math.h>
#include <assert.h>
#include <directxmath.h>
using namespace std;
using namespace DirectX;

class Vector3D
{
public:
	float x, y, z;
	Vector3D();
	Vector3D(float x1, float y1, float z1 = 0);
	Vector3D(const Vector3D& vec);

	operator XMFLOAT3();				// To XMFLOAT3
	operator XMMATRIX();				// To XMMATRIX
	operator XMVECTOR();				// To XMVECTOR
	bool operator>(const float value);
	bool operator>=(const float value);
	bool operator<(const float value);
	bool operator<=(const float value);
	Vector3D operator+(const Vector3D& vec);
	Vector3D operator+(const float value);
	Vector3D operator+=(const Vector3D& vec);
	Vector3D operator-(const Vector3D& vec);
	Vector3D operator-(const float value);
	Vector3D operator-=(const Vector3D& vec);
	Vector3D operator*(const Vector3D& vec);
	Vector3D operator*(const float value);
	Vector3D operator*=(const Vector3D& vec);
	Vector3D operator*=(const float value);
	Vector3D operator/(const Vector3D& vec);
	Vector3D operator/(const float value);
	Vector3D operator/=(const Vector3D& vec);
	Vector3D operator=(const Vector3D& vec);
	bool operator!=(const Vector3D& vec);

	float dot(const Vector3D& vec);
	Vector3D cross(const Vector3D& vec);
	Vector3D norm();

	static Vector3D fromXMVECTOR(const XMVECTOR& vec);
	static Vector3D fromXMFLOAT3(const XMFLOAT3& vec);

	float square();
	float dist(const Vector3D& vec);
	float magnitude();

	void addScaledVector(const Vector3D& vec, float scale);
	void clear() { x = 0; y = 0; z = 0; };

	float getX() { return x; };
	float getY() { return y; };
	float getZ() { return z; };

	void invert();

	~Vector3D();
};

