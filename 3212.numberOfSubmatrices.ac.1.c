#include "shdstd.h"

int numberOfSubmatrices(char **grid, int grid_size, int *grid_col_size)
{
	int rows = grid_size;
	int cols = grid_col_size[0];

	int *curr_x = malloc((cols+1) * sizeof(int));
	int *prev_x = malloc((cols+1) * sizeof(int));
	int *curr_y = malloc((cols+1) * sizeof(int));
	int *prev_y = malloc((cols+1) * sizeof(int));

	memset(prev_x, 0x00, (cols+1) * sizeof(int));
	memset(prev_y, 0x00, (cols+1) * sizeof(int));

	int count = 0;
	for (int r = 0; r < rows; ++r) {
		curr_x[0] = 0;
		curr_y[0] = 0;
		for (int c = 0; c < cols; ++c) {
			curr_x[c+1] = curr_x[c] + (grid[r][c] == 'X');
			curr_y[c+1] = curr_y[c] + (grid[r][c] == 'Y');
		}
		for (int c = 1; c <= cols; ++c) {
			curr_x[c] += prev_x[c];
			curr_y[c] += prev_y[c];

			if (curr_x[c] && curr_x[c] == curr_y[c]) {
				++count;
			}
		}

		int *tmp;
		tmp = prev_x;
		prev_x = curr_x;
		curr_x = tmp;

		tmp = prev_y;
		prev_y = curr_y;
		curr_y = tmp;
	}

	free(curr_x);
	free(prev_x);
	free(curr_y);
	free(prev_y);

	return count;
}
