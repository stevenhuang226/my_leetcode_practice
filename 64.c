#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

int minPathSum(int **grid, int size, int *p_col_size)
{
	int col_size = *p_col_size;
	int i,i2;
	for (i = 1; i < size; ++i) {
		grid[i][0] += grid[i-1][0];
	}

	for (i = 1; i < col_size; ++i) {
		grid[0][i] += grid[0][i-1];
	}

	for (i = 1; i < size; ++i) {
		for (i2 = 1; i2 < col_size; ++i2) {
			int up = grid[i-1][i2];
			int left = grid[i][i2-1];
			grid[i][i2] += MIN(up, left);
		}
	}

	int res = grid[size-1][col_size-1];

	return res;
}
