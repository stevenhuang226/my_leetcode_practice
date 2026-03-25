#include "shdstd.h"


#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int minTimeToVisitAllPoints(int **points, int size, int *col_size)
{
	int sum = 0;

	for (int i = 0; i < size - 1; ++i) {
		int xl = points[i][0];
		int yl = points[i][1];

		int xr = points[i+1][0];
		int yr = points[i+1][1];

		int dx = abs(xl - xr);
		int dy = abs(yl - yr);

		sum += MAX(dx, dy);
	}

	return sum;
}
