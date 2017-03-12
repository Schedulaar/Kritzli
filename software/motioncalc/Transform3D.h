#include "Matrix3D.h"
#include "Vector3D.h"

#pragma once
class Transform3D
{
public:
	Matrix3D matrix;
	Vector3D vector;
	Transform3D();
	Transform3D(Matrix3D matrix, Vector3D vector);

	Transform3D& operator=(Transform3D x);
	Transform3D& operator+=(const Transform3D& y);
	Transform3D& operator*=(const Transform3D& y);
	Transform3D& operator*=(const Matrix3D & y) {
		this->matrix *= y;
		return *this;
	}

	void print();
};

inline bool operator==(const Transform3D& x, const Transform3D& y);

inline bool operator!=(const Transform3D& x, Transform3D& y);

inline Transform3D operator+(Transform3D x, const Transform3D& y);

inline Vector3D operator*(Transform3D x, const Vector3D& y) {
	return x.matrix * y + x.vector;
}