#include "shdstd.h"

int comp(const void *a, const void *b)
{
	if ((*(int **)a)[1] < (*(int **)b)[1]) {
		return -1;
	}
	if ((*(int **)a)[1] > (*(int **)b)[1]) {
		return 1;
	}
	return 0;
}

int findMinArrowShots(int **points, int size, int *col_size)
{
	qsort(points, size, sizeof(int *), comp);

	int end = points[0][1];
	int count = 1;
	for (int i = 1; i < size; ++i) {
		if (points[i][0] <= end) {
			continue;
		}

		end = points[i][1];
		++count;
	}

	return count;
}

