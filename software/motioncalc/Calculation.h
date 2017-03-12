#include "Vector3D.h"

struct AngleSet
{
	long double angle1;
	long double angle2;
	long double angle3;
	long double angle4;
};

#pragma once
class Calculation
{
private:
	static int getMotor1AngleForPoint2D(long double z, long double x, long double *angle); /*-90°: */
	static Vector3D getMotor4Position(Vector3D *point, long double motor1angle);
	static Vector3D getMotor2Position(long double motor1angle);
	static int getMotor3Angle(const Vector3D *motor3, const Vector3D *motor4, long double motor1angle, long double motor2angle, long double *angle);
	static long double getMotor4Angle(long double motor2angle, long double motor3angle);
	static int getMotor3Position(long double motor1angle, const Vector3D *motor2, const Vector3D *motor4, Vector3D *p);
	static int getSchnittpktCircles2D(long double r, long double x2, long double y2, long double *x3, long double *y3);
	static int getMotor2Angle(const Vector3D *motor2, const Vector3D *motor3, long double motor1angle, long double *angle);
	static Vector3D getPenTopPosition(Vector3D *point);

public:
	static Vector3D getPenPositionFromAngles(long double angles[4], int debug);
	static int calcAngles(Vector3D *point, long double angles[4]);
	static int getPenPositionForVector3D(Vector3D *point, Vector3D *p);
};