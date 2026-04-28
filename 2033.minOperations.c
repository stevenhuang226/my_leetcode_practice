#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int cmp_i32(const void *l, const void *r)
{
	return *(int *)l - *(int *)r;
}

int minOperations(int **grid, int size, int *col_size, int x)
{
	int rows = size;
	int cols = col_size[0];

	int flat_size = rows * cols;
	int *flat = malloc(flat_size * sizeof(int));

	int sum = 0;

	int8_t brk = false;
	int chk = grid[0][0] % x;
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			int num = grid[r][c];
			if (chk != num % x) {
				brk = true;
				break;
			}
			int d = num / x;
			flat[r * cols + c] = d;
			sum += d;
		}
		if (brk) {
			break;
		}
	}

	if (brk) {
		free(flat);
		return -1;
	}
	qsort(flat, flat_size, sizeof(int), cmp_i32);

	int best = INT32_MAX;
	int pfx = 0;
	for (int i = 0; i < flat_size; ++i) {
		int ntail = flat_size - i;
		int n = flat[i];
		int sfx = sum - pfx;

		int operate = (sfx - ntail * n) + (i * n - pfx);
		best = MIN(best, operate);

		pfx += flat[i];
	}

	free(flat);

	return best;
}
