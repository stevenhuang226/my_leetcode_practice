#include "shdstd.h"

int countNegatives(int **grid, int size, int *col_size)
{
	int i,i2;
	int count = 0;
	for (i = 0; i < size; ++i) {
		for (i2 = 0; i2 < col_size[i]; ++i2) {
			if (grid[i][i2] < 0) {
				++count;
			}
		}
	}

	return count;
}
