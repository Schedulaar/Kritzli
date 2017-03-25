#include "Vector3D.h"

struct AngleSet
{
	double angle1;
	double angle2;
	double angle3;
	double angle4;
};

#pragma once
class Calculation
{
private:
	static int getMotor1AngleForPoint2D(double z, double x, double& angle); /*-90deg: */
	static Vector3D getMotor4Position(Vector3D &point, double motor1angle);
	static Vector3D getMotor2Position(double motor1angle);
	static int getMotor3Angle(const Vector3D& motor3, const Vector3D& motor4, double motor1angle, double motor2angle, double& angle);
	static double getMotor4Angle(double motor2angle, double motor3angle);
	static int getMotor3Position(double motor1angle, const Vector3D &motor2, const Vector3D &motor4, Vector3D &p);
	static int getSchnittpktCircles2D(double r, double x2, double y2, double& x3, double& y3);
	static int getMotor2Angle(const Vector3D& motor2, const Vector3D& motor3, double motor1angle, double& angle);
	static Vector3D getPenTopPosition(const Vector3D &point);

public:
	static Vector3D getPenPositionFromAngles(double angles[4], int debug = 0);
	static int calcAngles(const Vector3D& point, double angles[4]);
	static int getPenPositionForVector3D(const Vector3D& point, Vector3D& p);
};
