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

Matrix3D::Matrix3D(double val[3][3])
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

Matrix3D Matrix3D::fromRotation(int axis, double angle)
{
	if (axis == X_AXIS) {
		
		double values[3][3] = { { 1, 0, 0 }, { 0, cos(angle), -sin(angle) }, {0, sin(angle), cos(angle)} };
		return Matrix3D(values);
	}
	else if (axis == Y_AXIS) {
		double values[3][3] = { { cos(angle), 0, sin(angle) },{ 0, 1, 0},{ -sin(angle), 0, cos(angle) } };
		return Matrix3D(values);
	}
	double values[3][3] = { { cos(angle), -sin(angle), 0},{ sin(angle), cos(angle), 0 },{ 0, 0, 1 } };
	return Matrix3D(values);
}

inline Matrix3D operator+(Matrix3D x, const Matrix3D & y)
{
	return x += y;
}

inline Matrix3D operator*(Matrix3D x, const Matrix3D & y)
{
	double values[3][3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			double sum = 0;
			for (int k = 0; k < 3; k++) {
				sum += x.values[i][k] * y.values[k][j];
			}
			values[i][j] = sum;
		}
	}
	return Matrix3D(values);
}