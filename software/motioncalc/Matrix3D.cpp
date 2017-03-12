#include "Matrix3D.h"
#include <math.h>

Matrix3D::Matrix3D()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->values[i][j] = (i == j);
		}
	}
}

Matrix3D::Matrix3D(long double val[3][3])
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->values[i][j] = val[i][j];
		}
	}
}

Matrix3D & Matrix3D::operator=(Matrix3D x)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->values[i][j] = x.values[i][j];
		}
	}
	return *this;
}

Matrix3D & Matrix3D::operator+=(const Matrix3D & y)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->values[i][j] += y.values[i][j];
		}
	}
	return *this;
}

Matrix3D & Matrix3D::operator*=(const Matrix3D & y)
{
	*this = *this * y;
	return *this;
}

Matrix3D Matrix3D::fromRotation(int axis, long double angle)
{
	if (axis == X_AXIS) {
		
		long double values[3][3] = { { 1, 0, 0 }, { 0, cosl(angle), -sinl(angle) }, {0, sinl(angle), cosl(angle)} };
		return Matrix3D(values);
	}
	else if (axis == Y_AXIS) {
		long double values[3][3] = { { cosl(angle), 0, sinl(angle) },{ 0, 1, 0},{ -sinl(angle), 0, cosl(angle) } };
		return Matrix3D(values);
	}
	long double values[3][3] = { { cosl(angle), -sinl(angle), 0},{ sinl(angle), cosl(angle), 0 },{ 0, 0, 1 } };
	return Matrix3D(values);
}
	
inline bool operator==(const Matrix3D & x, const Matrix3D & y)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (x.values[i][j] != y.values[i][j])
				return false;
		}
	}
	return true;
}

inline bool operator!=(const Matrix3D & x, Matrix3D & y)
{
	return !operator==(x, y);
}

inline Matrix3D operator+(Matrix3D x, const Matrix3D & y)
{
	return x += y;
}

inline Matrix3D operator*(Matrix3D x, const Matrix3D & y)
{
	long double values[3][3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			long double sum = 0;
			for (int k = 0; k < 3; k++) {
				sum += x.values[i][k] * y.values[k][j];
			}
			values[i][j] = sum;
		}
	}
	return Matrix3D(values);
}