#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int cmp_inc(const void *l, const void *r)
{
	return *(int *)l - *(int *)r;
}

int **minAbsDiff(int **grid, int grid_size, int *grid_col_size,
		int k, int *ret_size, int **ret_col_size)
{
	int rows = grid_size;
	int cols = grid_col_size[0];

	int ret_rows = rows - k + 1;
	int ret_cols = cols - k + 1;

	int **result = malloc(ret_rows * sizeof(int *));
	int *result_flat = malloc(ret_rows * ret_cols * sizeof(int));
	(*ret_col_size) = malloc(ret_rows * sizeof(int));

	*ret_size = ret_rows;
	for (int i = 0; i < ret_rows; ++i) {
		result[i] = result_flat + i * ret_cols;
		(*ret_col_size)[i] = ret_cols;
	}

	int bfr_size = k * k;

	if (bfr_size == 1) {
		for (int r = 0; r < ret_rows; ++r) {
			for (int c = 0; c < ret_cols; ++c) {
				result[r][c] = 0;
			}
		}
		return result;
	}

	int *buffer = malloc(bfr_size * sizeof(int));

	for (int r = 0; r < ret_rows; ++r) {
		for (int c = 0; c < ret_cols; ++c) {
			int p = 0;
			for (int rk = 0; rk < k; ++rk) {
				for (int ck = 0; ck < k; ++ck) {
					buffer[p++] = grid[r + rk][c + ck];
				}
			}

			qsort(buffer, bfr_size, sizeof(int), cmp_inc);

			int min_gap = INT32_MAX;
			int dif = false;
			for (int i = 0; i < bfr_size - 1; ++i) {
				if (buffer[i+1] == buffer[i]) continue;
				min_gap = MIN(min_gap, buffer[i+1] - buffer[i]);
				dif = true;
			}

			if (dif == false) {
				result[r][c] = 0;
			} else {
				result[r][c] = min_gap;
			}
		}
	}

	free(buffer);

	return result;
}
