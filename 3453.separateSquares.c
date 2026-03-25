#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int comp(const void *l, const void *r)
{
	return (*(int **)l)[1] - (*(int **)r)[1];
}

double below(int **squares, int size, double y)
{
	int64_t int_sum = 0;
	double float_sum = 0;

	int i = 0;
	while (i < size && squares[i][1] < y) {
		int axis_y = squares[i][1];
		int64_t len = squares[i][2];
		++i;

		if (axis_y + len > y) {
			float_sum += len * (double)(y - axis_y);
			continue;
		}

		int_sum += len * len;
	}

	return (double)int_sum + float_sum;
}

double separateSquares(int **squares, int size, int *col_size)
{
	qsort(squares, size, sizeof(int *), comp);

	int64_t int_total_area = 0;

	int64_t int_top = 0;
	int64_t int_bottom = INT32_MAX;

	for (int i = 0; i < size; ++i) {
		int y = squares[i][1];
		int64_t len = squares[i][2];
		int_top = MAX(int_top, y + len);
		int_bottom = MIN(int_bottom, y);
		int_total_area += len * len;
	}

	double total_area = (double)int_total_area;

	double right = (double)int_top;
	double left = (double)int_bottom;

	while (right - left > 1e-6) {
		double mid = (left + right) / 2;

		double area_below = below(squares, size, mid);
		double area_above = total_area - area_below;

		if (area_above > area_below) {
			left = mid;
		} else {
			right = mid;
		}
	}

	return left;
}
