#include "shdstd.h"

bool canPartitionGrid(int **grid, int grid_size, int *grid_col_size)
{
	int rows = grid_size;
	int cols = grid_col_size[0];

	int64_t sum = 0;
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			sum += grid[r][c];
		}
	}

	int64_t rows_prefix = 0;
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			rows_prefix += grid[r][c];
		}

		if (rows_prefix * 2 == sum) {
			return true;
		}
	}


	int64_t cols_prefix = 0;
	for (int c = 0; c < cols; ++c) {
		for (int r = 0; r < rows; ++r) {
			cols_prefix += grid[r][c];
		}

		if (cols_prefix * 2 == sum) {
			return true;
		}
	}

	return false;
}
