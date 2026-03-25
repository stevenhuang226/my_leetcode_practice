#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int maximalRectangle(char **matrix, int size, int *col_size) {
	int col = size;
	int row = col_size[0];

	int **grid = malloc(col * sizeof(int *));
	int *grid_flat = malloc(col * row * sizeof(int));

	for (int i = 0; i < col; ++i) {
		grid[i] = grid_flat + i * row;
		grid[i][0] = matrix[i][0] - '0';
		for (int i2 = 0; i2 < row - 1; ++i2) {
			grid[i][i2+1] = (grid[i][i2] + 1) * (matrix[i][i2+1] - '0');
		}
	}

	int max = 0;

	for (int i = 0; i < row; ++i) {
		for (int i2 = 0; i2 < col; ++i2) {
			int min_width = INT32_MAX;
			for (int i3 = 0; i2 + i3 < col; ++i3) {
				min_width = MIN(min_width, grid[i2 + i3][i]);
				if (min_width == 0) {
					break;
				}
				max = MAX(max, min_width * (i3+1));
			}
		}
	}

	free(grid_flat);
	free(grid);

	return max;
}
