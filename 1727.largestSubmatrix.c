#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int cmp_consecutive(const void *l, const void *r)
{
	return *(int *)r - *(int *)l;
}

int largestSubmatrix(int **matrix, int size, int *col_size)
{
	int rows = size;
	int cols = col_size[0];


	int **consecutive = malloc(rows * sizeof(int *));
	int *consecutive_flat = malloc(rows * cols * sizeof(int));
	for (int i = 0; i < rows; ++i) {
		consecutive[i] = consecutive_flat + i * cols;
	}

	for (int c = 0; c < cols; ++c) {
		int combo = 0;
		for (int r = 0; r < rows; ++r) {
			if (matrix[r][c] == 1) {
				++combo;
			} else {
				combo = 0;
			}
			consecutive[r][c] = combo;
		}
	}

	for (int r = 0; r < rows; ++r) {
		qsort(consecutive[r], cols, sizeof(int), cmp_consecutive);
	}

	int best = 0;
	for (int r = 0; r < rows; ++r) {
		int min_height = INT32_MAX;
		for (int c = 0; c < cols; ++c) {
			min_height = MIN(min_height, consecutive[r][c]);
			best = MAX(best, min_height * (c+1));
		}
	}

	free(consecutive_flat);
	free(consecutive);

	return best;
}
