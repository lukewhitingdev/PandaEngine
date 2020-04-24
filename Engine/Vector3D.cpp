#include "Vector3D.h"



Vector3D::Vector3D()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3D::Vector3D(float x1, float y1, float z1)
{
	x = x1;
	y = y1;
	z = z1;
}

Vector3D::Vector3D(const Vector3D& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

#pragma region operators



Vector3D::operator XMFLOAT3()
{
	XMFLOAT3 float3 = XMFLOAT3(x, y, z);
	return float3;
}

Vector3D::operator XMMATRIX()
{
	XMFLOAT3X3 float3 = XMFLOAT3X3(x, 0.0f, 0.0f,
		y, 0.0f, 0.0f,
		z, 0.0f, 0.0f);
	return XMLoadFloat3x3(&float3);
}

Vector3D::operator XMVECTOR()
{
	XMVECTOR vector = XMVectorSet(x, y, z, 0);
	return vector;
}


bool Vector3D::operator>(const float value)
{
	if (x > value || y > value || z > value)
		return true;

	return false;
}

bool Vector3D::operator>=(const float value)
{
	if (x >= value || y >= value || z >= value)
		return true;

	return false;
}

bool Vector3D::operator<(const float value)
{
	if (x < value || y < value || z < value)
		return true;

	return false;
}

bool Vector3D::operator<=(const float value)
{
	if (x <= value || y <= value || z <= value)
		return true;

	return false;
}


Vector3D Vector3D::operator+(const Vector3D& vec)
{
	Vector3D outcome = Vector3D(x + vec.x, y + vec.y, z + vec.z);
	return outcome;
}

Vector3D Vector3D::operator+(const float value)
{
	Vector3D outcome = Vector3D(x + value, y + value, z + value);
	return outcome;
}

Vector3D Vector3D::operator+=(const Vector3D& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;

	return *this;
}

Vector3D Vector3D::operator-(const Vector3D& vec)
{
	Vector3D outcome = Vector3D(x - vec.x, y - vec.y, z - vec.z);
	return outcome;
}

Vector3D Vector3D::operator-(const float value)
{
	Vector3D outcome = Vector3D(x - value, y - value, z - value);
	return outcome;
}

Vector3D Vector3D::operator-=(const Vector3D& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;

	return *this;
}

Vector3D Vector3D::operator*(const Vector3D& vec)
{
	Vector3D outcome = Vector3D(x * vec.x, y * vec.y, z * vec.z);
	return outcome;
}

Vector3D Vector3D::operator*(const float value)
{
	Vector3D outcome = Vector3D(x * value, y * value, z * value);
	return outcome;
}

Vector3D Vector3D::operator*=(const Vector3D& vec)
{
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;

	return *this;
}

Vector3D Vector3D::operator*=(const float value)
{
	return Vector3D(x *= value, y *= value, z *= value);
}

Vector3D Vector3D::operator/(const Vector3D& vec)
{
	return Vector3D(x / vec.x, y / vec.y, z / vec.z);
}

Vector3D Vector3D::operator/(const float value)
{
	return Vector3D(x / value, y / value, z / value);
}

Vector3D Vector3D::operator/=(const Vector3D& vec)
{
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;

	return *this;
}

Vector3D Vector3D::operator=(const Vector3D& vec)
{
	return Vector3D(x = vec.x, y = vec.y, z = vec.z);
}

bool Vector3D::operator!=(const Vector3D& vec)
{
	if (x == vec.x && y == vec.y && z == vec.z)
		return true;
	return false;
}

#pragma endregion

#pragma region Calculations

float Vector3D::dot(const Vector3D& vec)
{
	return (x * vec.x + y * vec.y + z * vec.z);
}

Vector3D Vector3D::cross(const Vector3D& vec)
{
	float ni = y * vec.z - z * vec.y;
	float nj = x * vec.z - z * vec.x;
	float nk = x * vec.y - y * vec.x;
	return Vector3D(ni, nj, nk);
}

Vector3D Vector3D::norm()
{
	float magnitude = Vector3D::magnitude();
	return Vector3D(x / magnitude, y / magnitude, z / magnitude);
}

Vector3D Vector3D::fromXMVECTOR(const XMVECTOR& vec)
{
	XMFLOAT4 vector4;
	XMStoreFloat4(&vector4, vec);

	Vector3D vector3 = Vector3D(vector4.x, vector4.y, vector4.z);
	return vector3;
}

Vector3D Vector3D::fromXMFLOAT3(const XMFLOAT3& vec) {
	return Vector3D(vec.x, vec.y, vec.z);
}

float Vector3D::square()
{
	return (x * x + y * y + z * z);
}

float Vector3D::dist(const Vector3D& vec)
{
	float distX = (vec.x - x) * (vec.x - x);
	float distY = (vec.y - y) * (vec.y - y);
	float distZ = (vec.z - z) * (vec.z - z);
	return sqrt(distX + distY + distZ);
}

float Vector3D::magnitude()
{
	return sqrt(Vector3D::square()); // Cleanup later.
}

void Vector3D::addScaledVector(const Vector3D& vec, float scale)
{
	x += vec.x * scale;
	y += vec.y * scale;
	z += vec.z * scale;
}


#pragma endregion

void Vector3D::invert()
{
	x = -x;
	y = -y;
	z = -z;
}


Vector3D::~Vector3D()
{
}
