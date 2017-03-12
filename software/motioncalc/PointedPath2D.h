#include <vector>
#include "Calculation.h"
#pragma once
class PointedPath2D
{
private:
	const long double max_point_dist = 0.2;
public:
	PointedPath2D *next;
	bool paintToNext;
	long double x;
	long double y;
	std::vector<AngleSet> calcAngleList();
};

