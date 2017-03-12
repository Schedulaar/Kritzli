#include "Vector3D.h"
#include <math.h>

Vector3D::Vector3D()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3D::Vector3D(long double x, long double y, long double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D & Vector3D::operator=(Vector3D x)
{
	this->x = x.x;
	this->y = x.y;
	this->z = x.z;
	return *this;
}

Vector3D & Vector3D::operator+=(const Vector3D & y)
{
	this->x += y.x;
	this->y += y.y;
	this->z += y.z;
	return *this;
}

Vector3D & Vector3D::operator-=(const Vector3D & y)
{
	this->x -= y.x;
	this->y -= y.y;
	this->z -= y.z;
	return *this;
}

long double Vector3D::getLength() const
{
	return sqrtl(x*x + y*y + z*z);
}

inline bool operator==(const Vector3D & x, const Vector3D & y)
{
	return x.x == y.x && x.y == y.y && x.z == y.z;
}

inline bool operator!=(const Vector3D & x, Vector3D & y)
{
	return !operator==(x, y);
}
