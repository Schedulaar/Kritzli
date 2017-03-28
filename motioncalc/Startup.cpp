#include "Calculation.h"
#include <stdio.h>
int main()
{
	Vector3D out;
	if(!Calculation::getPenPositionForVector3D(Vector3D(0, 0, 10), out))
		return 1;
	printf("%lf, %lf, %lf\n", out.x, out.y, out.z);
	return 0;
}