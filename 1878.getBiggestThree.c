#include "shdstd.h"

typedef struct {
	int r;
	int c;
} Point;

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
void update_answer(int *result, int curr_sum, int *res_upd)
{
	if (curr_sum <= result[2]) {
		return;
	}

	if (curr_sum > result[2] && curr_sum < result[1]) {
		result[2] = curr_sum;
		++(*res_upd);
		return;
	}
	if (curr_sum > result[1] && curr_sum < result[0]) {
		result[2] = result[1];
		result[1] = curr_sum;
		++(*res_upd);
		return;
	}
	if (curr_sum > result[0]) {
		result[2] = result[1];
		result[1] = result[0];
		result[0] = curr_sum;
		++(*res_upd);
		return;
	}
}

int *getBiggestThree(int **grid, int grid_size, int *grid_col_size, int *ret_size)
{
	int rows = grid_size;
	int cols = grid_col_size[0];

	int *result = calloc(3, sizeof(int));
	int res_upd = 0;

	int **tlbr = malloc((rows+1) * sizeof(int *));
	int *tlbr_flat = malloc((rows+1) * (cols+1) * sizeof(int));
	for (int i = 0; i <= rows; ++i) {
		tlbr[i] = tlbr_flat + i * (cols+1);
	}

	int **trbl = malloc((rows+1) * sizeof(int *));
	int *trbl_flat = malloc((rows+1) * (cols+1) * sizeof(int));
	for (int i = 0; i <= rows; ++i) {
		trbl[i] = trbl_flat + i * (cols+1);
	}

	for (int i = 1; i < rows; ++i) {
		int r = i;
		int c = 0;
		tlbr[r][c] = 0;
		while (c < cols && r < rows) {
			tlbr[r+1][c+1] = tlbr[r][c] + grid[r][c];
			++r; ++c;
		}

		r = i;
		c = cols;
		trbl[r][c] = 0;
		while (c > 0 && r < rows) {
			trbl[r+1][c-1] = trbl[r][c] + grid[r][c-1];
			++r; --c;
		}
	}

	for (int i = 0; i < cols; ++i) {
		int r = 0;
		int c = i;
		tlbr[r][c] = 0;
		while (c < cols && r < rows) {
			tlbr[r+1][c+1] = tlbr[r][c] + grid[r][c];
			++r; ++c;
		}
	}

	for (int i = cols; i > 0; --i) {
		int r = 0;
		int c = i;
		trbl[r][c] = 0;
		while (c > 0 && r < rows) {
			trbl[r+1][c-1] = trbl[r][c] + grid[r][c-1];
			++r; --c;
		}
	}

	int size_lim = MIN(rows, cols);

	for (int size = 1; size < size_lim; ++size) {
		for (int r = 0 + size; r + size < rows; ++r) {
			for (int c = 0 + size; c + size < cols; ++c) {
				Point top = {r - size, c};
				Point right = {r, c + size};
				Point left = {r, c - size};
				Point bottom = {r + size, c};

				int sum = 0;
				sum +=
					tlbr[right.r+1][right.c+1] -
					tlbr[top.r][top.c];
				sum +=
					tlbr[bottom.r+1][bottom.c+1] -
					tlbr[left.r][left.c];
				sum +=
					trbl[left.r][left.c+1] -
					trbl[top.r+1][top.c];
				sum +=
					trbl[bottom.r][bottom.c+1] -
					trbl[right.r+1][right.c];

				update_answer(result, sum, &res_upd);
			}
		}
	}

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			update_answer(result, grid[r][c], &res_upd);
		}
	}

	free(tlbr);
	free(tlbr_flat);
	free(trbl);
	free(trbl_flat);

	if (res_upd >= 3) {
		*ret_size = 3;
	} else {
		*ret_size = res_upd;
	}
	return result;
}
