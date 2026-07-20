#include "shdstd.h"



int **shiftGrid(int **grid, int grid_size, int *grid_col_size,
	int offset,
	int *ret_size, int **ret_col_size)
{
	int rows = grid_size;
	int cols = grid_col_size[0];
	int cells = rows * cols;

	int **res = malloc(rows * sizeof(int *));
	(*ret_col_size) = malloc(rows * sizeof(int));
	int *res_flat = malloc(rows * cols * sizeof(int));
	for (int i = 0; i < rows; ++i) {
		res[i] = res_flat + i * cols;
		(*ret_col_size)[i] = cols;
	}
	*ret_size = rows;

	for (int i = 0; i < cells; ++i) {
		int curr_r = i / cols;
		int curr_c = i % cols;

		int trg = (i + offset) % cells;
		int trg_r = trg / cols;
		int trg_c = trg % cols;

		res[trg_r][trg_c] = grid[curr_r][curr_c];
	}

	return res;
}
