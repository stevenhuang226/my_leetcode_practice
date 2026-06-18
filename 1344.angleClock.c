#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
double sfmin(const double a, const double b)
{
	return MIN(a, b);
}

double angleClock(int hour, int minutes)
{
	double hour_gap = 360 / 12;
	double min_gap = 360 / 60;

	hour %= 12;

	double hour_degree = (double)(hour) * hour_gap + (double)hour_gap * ((double)minutes / (double)60);
	double min_degree = (double)(minutes) * min_gap;

	double a = fabs(hour_degree - min_degree);
	double b = fabs((double)360 - min_degree + hour_degree);
	double c = fabs((double)360 - hour_degree + min_degree);

	return sfmin(sfmin(a, b), c);
}
