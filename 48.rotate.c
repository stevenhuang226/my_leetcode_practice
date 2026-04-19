#include "shdstd.h"

static inline void swap_i32(int *l, int *r)
{
	*l ^= *r;
	*r ^= *l;
	*l ^= *r;
}

static inline void swap_ptr(void **l, void **r)
{
	void *tmp = *l;
	*l = *r;
	*r = tmp;
}

void rotate(int **matrix, int size, int *col_size)
{
	int rows = size;
	int cols = col_size[0];

	for (int i = 0; i * 2 < size; ++i) {
		swap_ptr((void *)&matrix[i], (void *)&matrix[size-i-1]);
	}

	for (int r = 0; r < rows; ++r) {
		for (int c = r + 1; c < cols; ++c) {
			swap_i32(&matrix[r][c], &matrix[c][r]);
		}
	}
}
