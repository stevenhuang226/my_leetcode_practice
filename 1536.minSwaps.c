#include "shdstd.h"

int minSwaps(int **grid, int grid_size, int *grid_col_size)
{
	int *rear_zero = malloc(grid_size * sizeof(int));
	int rz_count = 0;

	int rows = grid_size;
	int cols = grid_col_size[0];

	for (int r = 0; r < grid_size; ++r) {
		int combo = 0;
		for (int c = cols - 1; c >= 0; --c) {
			if (grid[r][c] != 0) {
				break;
			} else {
				++combo;
			}
		}
		rear_zero[rz_count++] = combo;
	}

	int swap = 0;
	for (int r = 0; r < rows; ++r) {
		int trg_zero = cols - r - 1;

		int8_t find = false;
		int sr;
		for (sr = r; sr < rows; ++sr) {
			if (rear_zero[sr] >= trg_zero) {
				find = true;
				break;
			}
		}

		if (! find) {
			free(rear_zero);
			return -1;
		}

		swap += sr - r;
		for (; sr > r; --sr) {
			int tmp = rear_zero[sr-1];
			rear_zero[sr-1] = rear_zero[sr];
			rear_zero[sr] = tmp;
		}
	}

	free(rear_zero);
	return swap;
}
