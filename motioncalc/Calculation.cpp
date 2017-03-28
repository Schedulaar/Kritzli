#define _USE_MATH_DEFINES
#include "Calculation.h"
#include "Transform3D.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>

/*x-Achse: Mitte Papier*/
/*y-Achse: Hoehe*/
/*z-Achse: Kante Fuss Papier*/
const double pen_length = 0; /*laenge ab loch unten */
const Vector3D nullToMotor1(-4, 4.65, 0);
const Vector3D motor1tomotor2(2.112019, 3.700, 1.600);
const Vector3D arm1_horizontal(10.4345, 0.000, -0.600);
const Vector3D arm2_horizontal(10.3655, 0.000, -1.350);
const Vector3D motor4ToPenHolderCenter(0, 0, -1.147); //TODO
const Vector3D penHolderCenterToPenTop(0, -1.003, 0); //TODO
const Vector3D motor4ToPenTop = motor4ToPenHolderCenter + penHolderCenterToPenTop;
const Vector3D PenTopToPenTip(0, -pen_length, 0);


Vector3D Calculation::getPenPositionFromAngles(double angles[4], int debug) {
	if (debug) printf("Motor1:\n");
	Transform3D tr = Transform3D(Matrix3D(), nullToMotor1);
	if(debug) tr.print();
	tr *= Matrix3D::fromRotation(Y_AXIS, angles[0]);
	if (debug) tr.print();
	if (debug) printf("Motor2:\n");
	tr *= Transform3D(Matrix3D(), motor1tomotor2);
	if (debug) tr.print();
	tr *= Matrix3D::fromRotation(Z_AXIS, angles[1]);
	if (debug) tr.print();
	if (debug) printf("Motor3:\n");
	tr *= Transform3D(Matrix3D(), arm1_horizontal);
	if (debug) tr.print();
	tr *= Matrix3D::fromRotation(Z_AXIS, angles[2]);
	if (debug) tr.print();
	if (debug) printf("Motor4:\n");
	tr *= Transform3D(Matrix3D(), arm2_horizontal);
	if (debug) tr.print();
	tr *= Matrix3D::fromRotation(Z_AXIS, angles[3]);
	if (debug) tr.print();
	if (debug) printf("Pentip:\n");
	tr *= Transform3D(Matrix3D(), motor4ToPenTop + PenTopToPenTip);
	if (debug) tr.print();

	return tr * Vector3D();
}

int Calculation::calcAngles(const Vector3D& point, double angles[4]){
	if (!Calculation::getMotor1Angle(point.z, point.x, angles[0])) /*should finally work now*/
		return 0;

	Vector3D motor2 = Calculation::getMotor2Position(angles[0]); /*should always work*/
	Vector3D motor4 = Calculation::getMotor4Position(point, angles[0]); /*should work now*/

	Vector3D motor3;
	if (!Calculation::getMotor3Position(angles[0], motor2, motor4, motor3))
		return 0;

	Vector3D d1 = motor3 - motor2;
	Vector3D d2 = motor4 - motor3;

	if (!Calculation::getMotor2Angle(motor2, motor3, angles[0], angles[1]))
		return 0;

	if (!Calculation::getMotor3Angle(motor3, motor4, angles[0], angles[1], angles[2]))
		return 0;

	angles[3] = Calculation::getMotor4Angle(angles[1], angles[2]);
	return 1;
}

int Calculation::getPenPositionForVector3D(const Vector3D& point, Vector3D& p) {
	double angles[4];
	if (!Calculation::calcAngles(point, angles))
		return 0;

	p = Calculation::getPenPositionFromAngles(angles, true);
	return 1;
}

Vector3D Calculation::getPenTopPosition(const Vector3D& point) { /*for exact vertical pen*/
	return point - PenTopToPenTip;
}

/* -90deg positiv z (nach rechts), 90deg negativ z (nach links) */
int Calculation::getMotor1Angle(double z, double x, double& angle) { 
	const double r = nullToMotor1.z + motor1tomotor2.z + arm1_horizontal.z + arm2_horizontal.z + motor4ToPenTop.z;
	double l = sqrt(pow(x - nullToMotor1.x, 2) + pow(z, 2));
	double gamma = atan(z / (x -nullToMotor1.x));
	double beta = asin(fabs(r / l));
	angle = - gamma - beta;
	return angle != NAN;
}

Vector3D Calculation::getMotor2Position(double motor1angle) {
	Transform3D tr = Transform3D(Matrix3D(), nullToMotor1);
	tr *= Matrix3D::fromRotation(Y_AXIS, motor1angle);
	tr *= Transform3D(Matrix3D(), motor1tomotor2);
	return tr * Vector3D();;
}

Vector3D Calculation::getMotor4Position(const Vector3D& point, double motor1angle) {
	Vector3D penHolderCenter = getPenTopPosition(point) - penHolderCenterToPenTop;
	double beta = M_PI_2 - motor1angle;
	double delta_z = sin(beta) * motor4ToPenHolderCenter.getLength();
	double delta_x = cos(beta) * motor4ToPenHolderCenter.getLength();
	return penHolderCenter + Vector3D(delta_x, 0, delta_z);
}

/*TODO: different radius */
int Calculation::getSchnittpktCircles2D(double r1, double r2, double x2, double y2, double& x3, double& y3) {
	double angle = atan(y2 / x2);
	double l = sqrt(x2*x2 + y2*y2);
	if (r1 + r2 < l)
		return 0;
	double x = 0.5 * (r1 - r2 + l);
	double y = sqrt(r1*r1 - x*x);
	Vector3D v = Matrix3D::fromRotation(Z_AXIS, angle) * Vector3D(x, y, 0);
	x3 = v.x;
	y3 = v.y;
	return 1;
}

int Calculation::getMotor3Position(double motor1angle, const Vector3D& motor2, const Vector3D& motor4, Vector3D& p) {
	Vector3D d = Matrix3D::fromRotation(Y_AXIS, -motor1angle) * (motor4 - motor2);
	Vector3D sp;
	if (!getSchnittpktCircles2D(arm1_horizontal.x, arm2_horizontal.x, d.x, d.y, sp.x, sp.y))
		return 0;
	sp.z = arm1_horizontal.z;
	sp = Matrix3D::fromRotation(Y_AXIS, motor1angle) * sp;
	p = motor2 + sp;
	return 1;
}

/*90deg points to positive y-axis, -90deg points to negative y-axis*/
int Calculation::getMotor2Angle(const Vector3D& motor2, const Vector3D& motor3, double motor1angle, double& angle) { 
	Vector3D d = motor3 - motor2;
	d = Matrix3D::fromRotation(Y_AXIS, -motor1angle) * d;
	angle = atan(fabs(d.y / d.x));
	if (d.y >= 0 && d.x >= 0) { /*do nothing */ }
	else if (d.y >= 0 && d.x < 0) { angle = M_PI - angle; }
	else if (d.y < 0 && d.x >= 0) { angle = -angle; }
	else if (d.y < 0 && d.x < 0) { angle = angle - M_PI; }
	else assert(false);

	return angle != NAN;
}

/*90deg points to positive y-axis, -90deg points to negative y-axis (when motor2angle == 0)*/
int Calculation::getMotor3Angle(const Vector3D& motor3, const Vector3D& motor4, double motor1angle, double motor2angle, double& angle){
	if (!getMotor2Angle(motor3, motor4, motor1angle, angle))
		return 0;
	angle -= motor2angle;
	return 1;
}

double Calculation::getMotor4Angle(double motor2angle, double motor3angle) {
	return - motor3angle - motor2angle;
}