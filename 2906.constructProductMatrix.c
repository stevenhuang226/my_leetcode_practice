#include "shdstd.h"

#define MOD 12345

int **constructProductMatrix(int **grid, int grid_size, int *grid_col_size, int *ret_size, int **ret_col_size)
{
	int rows = grid_size;
	int cols = grid_col_size[0];

	int *suffix = malloc((rows * cols + 1) * sizeof(int));
	suffix[rows * cols] = 1;

	int64_t suffix_num = 1;
	for (int r = rows - 1; r >= 0; --r) {
		for (int c = cols - 1; c >= 0; --c) {
			suffix_num = (suffix_num * grid[r][c]) % MOD;
			suffix[(r*cols) + c] = suffix_num;
		}
	}

	int **result = malloc(rows * sizeof(int *));
	int *result_flat = malloc(rows * cols * sizeof(int));
	for (int i = 0; i < rows; ++i) {
		result[i] = result_flat + i * cols;
	}

	int64_t prefix_num = 1;
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			result[r][c] = (suffix[(r*cols) + c + 1] * prefix_num) % MOD;
			prefix_num = (prefix_num * grid[r][c]) % MOD;
		}
	}

	*ret_size = rows;
	(*ret_col_size) = malloc(rows * sizeof(int));
	for (int i = 0; i < rows; ++i) {
		(*ret_col_size)[i] = cols;
	}

	free(suffix);

	return result;
}
