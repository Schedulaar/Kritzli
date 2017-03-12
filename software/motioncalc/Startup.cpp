#include "Calculation.h"

int main() {
	Vector3D v;
	Calculation::getPenPositionForVector3D(&Vector3D(12, 0, 0.005 - 1.604 - 1.536 - 1.536 - 1.147), &v);
	Calculation::getPenPositionForVector3D(&Vector3D(5, 0, -3), &v);
	Calculation::getPenPositionForVector3D(&Vector3D(6, 0, -1), &v);
	Calculation::getPenPositionForVector3D(&Vector3D(8, 0, 5), &v);
	Calculation::getPenPositionForVector3D(&Vector3D(7, 0, 5), &v);
	Calculation::getPenPositionForVector3D(&Vector3D(10, 0, 5), &v);
	Calculation::getPenPositionForVector3D(&Vector3D(5, 0, 13), &v);
	Calculation::getPenPositionForVector3D(&Vector3D(0, 0, 5), &v); /*ungenau?!*/
}