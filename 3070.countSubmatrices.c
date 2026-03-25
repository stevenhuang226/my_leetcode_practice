#include "shdstd.h"

int countSubmatrices(int **grid, int grid_size, int *grid_col_size, int limit)
{
	int rows = grid_size;
	int cols = grid_col_size[0];

	int **area_prefix = malloc((rows+1) * sizeof(int *));
	int *area_prefix_flat = malloc((rows+1) * (cols+1) * sizeof(int));
	for (int i = 0; i <= rows; ++i) {
		area_prefix[i] = area_prefix_flat + i * (cols+1);
	}

	for (int r = 0; r < rows; ++r) {
		area_prefix[r+1][0] = 0;
		for (int c = 0; c < cols; ++c) {
			area_prefix[r+1][c+1] =
				area_prefix[r+1][c] + grid[r][c];
			if (area_prefix[r+1][c+1] > limit) {
				break;
			}
		}
	}

	int count;

	for (int c = 1; c <= cols; ++c) {
		area_prefix[0][c] = 0;
		for (int r = 0; r < rows; ++r) {
			area_prefix[r+1][c] =
				area_prefix[r][c] + area_prefix[r+1][c];
			if (area_prefix[r+1][c] > limit) {
				break;
			} else {
				++count;
			}
		}
	}

	free(area_prefix_flat);
	free(area_prefix);

	return count;
}
