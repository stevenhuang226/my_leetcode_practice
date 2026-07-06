#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int cmp_intervals(const void *l, const void *r)
{
	if ((*(int **)l)[0] != (*(int **)r)[0]) {
		return (*(int **)l)[0] - (*(int **)r)[0];
	} else {
		return (*(int **)r)[1] - (*(int **)l)[1];
	}
}

int removeCoveredIntervals(int **intervals, int size, int *col_size)
{
	qsort(intervals, size, sizeof(int *), cmp_intervals);

	int rm_count = 0;
	int prev_start = intervals[0][0];
	int prev_end = intervals[0][1];
	for (int i = 1; i < size; ++i) {
		int curr_start = intervals[i][0];
		int curr_end = intervals[i][1];

		if (prev_start <= curr_start && curr_end <= prev_end) {
			++rm_count;
			continue;
		}

		prev_start = curr_start;
		prev_end = MAX(prev_end, curr_end);
	}

	return size - rm_count;
}
