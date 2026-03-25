#include "shdstd.h"

int numberOfSubmatrices(char **grid, int grid_size, int *grid_col_size)
{
	int rows = grid_size;
	int cols = grid_col_size[0];

	int **prefix = malloc((rows+1) * sizeof(int *));
	int *prefix_flat = malloc((rows+1) * (cols+1) * sizeof(int));
	for (int i = 0; i <= rows; ++i) {
		prefix[i] = prefix_flat + i * (cols+1);
	}
	prefix[0][0] = 0;

	for (int r = 0; r < rows; ++r) {
		prefix[r+1][0] = 0;
		for (int c = 0; c < cols; ++c) {
			prefix[r+1][c+1] = prefix[r+1][c];
			if (grid[r][c] == 'X') {
				++prefix[r+1][c+1];
			} else if (grid[r][c] == 'Y') {
				--prefix[r+1][c+1];
			}
		}
	}

	for (int c = 1; c <= cols; ++c) {
		prefix[0][c] = 0;
		for (int r = 0; r < rows; ++r) {
			prefix[r+1][c] = prefix[r][c] + prefix[r+1][c];
		}
	}

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			if (grid[r][c] == '.') {
				grid[r][c] = 'b';
			} else {
				break;
			}
		}
	}
	for (int c = 0; c < cols; ++c) {
		for (int r = 0; r < rows; ++r) {
		}
	}

	int count = 0;
	for (int r = 1; r <= rows; ++r) {
		for (int c = 1; c <= cols; ++c) {
			if (prefix[r][c] == 0) {
				++count;
			}
		}
	}

	free(prefix_flat);
	free(prefix);

	return count;
}
