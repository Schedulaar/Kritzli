#include "Transform3D.h"
#include "Matrix3D.h"
#include <stdio.h>

Transform3D::Transform3D()
{
	this->matrix = Matrix3D();
	this->vector = Vector3D(0,0,0);
}

Transform3D::Transform3D(Matrix3D matrix, Vector3D vector)
{
	this->matrix = matrix;
	this->vector = vector;
}

Transform3D & Transform3D::operator=(Transform3D x)
{
	this->matrix = x.matrix;
	this->vector = x.vector;
	return *this;
}

Transform3D & Transform3D::operator+=(const Transform3D & y)
{
	this->matrix += y.matrix;
	this->vector += y.vector;
	return *this;
}
Transform3D & Transform3D::operator*=(const Transform3D & y)
{
	this->matrix *= y.matrix;
	this->vector += (this->matrix * y.vector);
	return *this;
}
void Transform3D::print()
{
	printf("( %5.2lf %5.2lf %5.2lf )   ( %5.2lf )\n", matrix.values[0][0], matrix.values[0][1], matrix.values[0][2], vector.x);
	printf("( %5.2lf %5.2lf %5.2lf ) + ( %5.2lf )\n", matrix.values[1][0], matrix.values[1][1], matrix.values[1][2], vector.y);
	printf("( %5.2lf %5.2lf %5.2lf )   ( %5.2lf )\n\n", matrix.values[2][0], matrix.values[2][1], matrix.values[2][2], vector.z);
}
inline bool operator==(const Transform3D & x, const Transform3D & y)
{
	return x.matrix == y.matrix && x.vector == y.vector;
}

inline bool operator!=(const Transform3D & x, Transform3D & y)
{
	return !operator==(x, y);
}

inline Transform3D operator+(Transform3D x, const Transform3D & y)
{
	return x += y;
}

inline Transform3D operator*(Transform3D x, const Transform3D & y)
{
	return x *= y;
}
