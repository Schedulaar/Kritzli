#include "Vector3D.h"

class MotionPerform {
	private:
		double lastAngles[4];
		void (*writeAngles)(double angles[4]);
		void (*waitForMotion)(int millisecs);
	public:
		MotionPerform(void (*writeAngles)(double [4]), void (*waitForMotion)(int));
		MotionPerform(void (*writeAngles)(double [4]), void (*waitForMotion)(int), double lastAngles[4]);
		void goTo(double angles[4], int count = 100);
		void calcAndGo(const Vector3D& point, int count = 100);
		void drawLine(const Vector3D& start, const Vector3D& fin);
		void drawPoint(const Vector3D& point);
};