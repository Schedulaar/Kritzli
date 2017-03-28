#include "Vector3D.h"

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

#pragma once
class Matrix3D
{
public:
	double values[3][3];
	Matrix3D();
	Matrix3D(double val[3][3]);
	Matrix3D& operator=(Matrix3D x);
	Matrix3D& operator+=(const Matrix3D& y);
	Matrix3D& operator*=(const Matrix3D& y);
	static Matrix3D fromRotation(int axis, double angle);
};

inline bool operator==(const Matrix3D& x, const Matrix3D& y){
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (x.values[i][j] != y.values[i][j])
				return false;
		}
	}
	return true;
}

inline bool operator!=(const Matrix3D& x, Matrix3D& y){
	return !operator==(x, y);
}

inline Matrix3D operator+(Matrix3D x, const Matrix3D& y);

inline Matrix3D operator*(Matrix3D x, const Matrix3D& y);

inline Vector3D operator*(const Matrix3D& x, const Vector3D& y) {
	return Vector3D(x.values[0][0] * y.x + x.values[0][1] * y.y + x.values[0][2] * y.z,
		x.values[1][0] * y.x + x.values[1][1] * y.y + x.values[1][2] * y.z,
		x.values[2][0] * y.x + x.values[2][1] * y.y + x.values[2][2] * y.z);
}
