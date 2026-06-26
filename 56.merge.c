#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int cmp_interval(const void *left, const void *right)
{
	int start_left = (*(int **)left)[0];
	int start_right = (*(int **)right)[0];

	int end_left = (*(int **)left)[1];
	int end_right = (*(int **)right)[1];

	if (start_left != start_right) {
		return start_left - start_right;
	}

	return end_left - end_right;
}

int **merge(int **intervals, int size, int *col_size, int *ret_size, int **ret_col_size)
{
	qsort(intervals, size, sizeof(int *), cmp_interval);

	int **res = malloc(size * sizeof(int *));
	int *res_flat = malloc(size * 2 * sizeof(int));
	int res_size = 0;

	(*ret_col_size) = malloc(size * sizeof(int));

	int interval_start = intervals[0][0];
	int interval_end = intervals[0][1];
	for (int i = 0; i < size; ++i) {
		int curr_start = intervals[i][0];
		int curr_end = intervals[i][1];

		if (curr_start <= interval_end) {
			interval_end = MAX(interval_end, curr_end);
			continue;
		}

		res[res_size] = res_flat + res_size * 2;
		res[res_size][0] = interval_start;
		res[res_size][1] = interval_end;
		(*ret_col_size)[res_size] = 2;
		++res_size;

		interval_start = curr_start;
		interval_end = curr_end;
	}
	res[res_size] = res_flat + res_size * 2;
	res[res_size][0] = interval_start;
	res[res_size][1] = interval_end;
	(*ret_col_size)[res_size] = 2;
	++res_size;

	*ret_size = res_size;

	return res;
}
