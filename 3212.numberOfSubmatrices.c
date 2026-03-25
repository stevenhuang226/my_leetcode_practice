#include "shdstd.h"

int numberOfSubmatrices(char **grid, int grid_size, int *grid_col_size)
{
	int rows = grid_size;
	int cols = grid_col_size[0];

	int *prev_x = calloc(cols, sizeof(int));
	int *prev_y = calloc(cols, sizeof(int));

	int count = 0;

	for (int r = 0; r < rows; ++r) {
		int curr_x = 0;
		int curr_y = 0;

		for (int c = 0; c < cols; ++c) {
			curr_x += (grid[r][c] == 'X');
			curr_y += (grid[r][c] == 'Y');

			prev_x[c] += curr_x;
			prev_y[c] += curr_y;

			if (prev_x[c] && prev_x[c] == prev_y[c]) {
				++count;
			}
		}
	}

	free(prev_x);
	free(prev_y);

	return count;
}
