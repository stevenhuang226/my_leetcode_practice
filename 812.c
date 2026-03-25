#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

double largestTriangleArea(int **points, int pointsSize, int *pointsColSize);

int main()
{
	return 0;
}


double largestTriangleArea(int **points, int pointsSize, int *pointsColSize)
{
	int i,ii,iii;
	double maximum_area  = 0.0f;
	for (i = 0; i < pointsSize; i++) {
		int i0 = points[i][0];
		int i1 = points[i][1];
		for (ii = i + 1; ii < pointsSize; ii++) {
			int ii0 = points[ii][0];
			int ii1 = points[ii][1];
			for (iii = ii + 1; iii < pointsSize; iii++) {
				double triangle_area = abs(i0 * (ii1 - points[iii][1]) +
					ii0 * (points[iii][1] - i1) +
					points[iii][0] * (i1 - ii1));
				if (triangle_area > maximum_area) {
					maximum_area = triangle_area;
				}
			}
		}
	}

	return (double)maximum_area * 0.5;
}
