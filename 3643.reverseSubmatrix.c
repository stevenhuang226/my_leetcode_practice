#include "shdstd.h"

int **reverseSubmatrix(int **grid, int grid_size, int *grid_col_size,
		int start_row, int start_col, int side_length,
		int *ret_size, int **ret_col_size)
{
	int rows = grid_size;
	int cols = grid_col_size[0];

	int **result = malloc(rows * sizeof(int *));
	int *result_flat = malloc(rows * cols * sizeof(int));

	*ret_size = rows;
	*ret_col_size = malloc(rows * sizeof(int));

	for (int i = 0; i < rows; ++i) {
		result[i] = result_flat + i * cols;
		(*ret_col_size)[i] = cols;
	}


	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			result[r][c] = grid[r][c];
		}
	}

	for (int r = 0; r < side_length; ++r) {
		int read_r = r + start_row;
		int write_r = start_row + side_length - r - 1;
		for (int c = 0; c < side_length; ++c) {
			int read_c = c + start_col;
			int write_c = c + start_col;
			result[write_r][write_c] = grid[read_r][read_c];
		}
	}

	return result;
}
