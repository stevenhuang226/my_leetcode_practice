#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int **insert(int **intervals, int intervals_size, int *intervals_col_size,
		int *new_interval, int new_interval_size,
		int *ret_size, int **ret_col_size)
{
	int **res = malloc((intervals_size+1) * sizeof(int *));
	int *res_flat = malloc((intervals_size+1) * 2 * sizeof(int));
	for (int i = 0; i <= intervals_size; ++i) {
		res[i] = res_flat + i * 2;
	}
	int r = 0;

	int new_start = new_interval[0];
	int new_end = new_interval[1];

	int p = 0;
	while (p < intervals_size && intervals[p][1] < new_start) {
		res[r][0] = intervals[p][0];
		res[r][1] = intervals[p][1];
		++r; ++p;
	}
	int curr_start;
	if (p < intervals_size) {
		curr_start = intervals[p][0];
	} else {
		curr_start = INT32_MAX;
	}
	int start = MIN(new_start, curr_start);
	int prev_end = 0;
	while (p < intervals_size && intervals[p][0] <= new_end) {
		prev_end = intervals[p][1];
		++p;
	}
	int end = MAX(new_end, prev_end);
	res[r][0] = start; res[r][1] = end; ++r;

	for (; p < intervals_size; ++p, ++r) {
		res[r][0] = intervals[p][0];
		res[r][1] = intervals[p][1];
	}

	int res_size = r;

	*ret_size = res_size;
	*ret_col_size = malloc(res_size * sizeof(int));
	for (int i = 0; i < res_size; ++i) {
		(*ret_col_size)[i] = 2;
	}

	return res;
}
