#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int64_t largestSquareArea(int **bl, int bl_size, int *bl_col_szie,
		int **tr, int tr_size, int *tr_col_size)
{
	int64_t max_edge = 0;

	for (int i = 0; i < bl_size; ++i) {
		for (int i2 = i + 1; i2 < bl_size; ++i2) {
			int64_t width = MIN(tr[i][0], tr[i2][0]) - MAX(bl[i][0], bl[i2][0]);
			int64_t height = MIN(tr[i][1], tr[i2][1]) - MAX(bl[i][1], bl[i2][1]);
			int64_t min_side = MIN(width, height);
			max_edge = MAX(max_edge, min_side);
		}
	}

	return max_edge * max_edge;
}
