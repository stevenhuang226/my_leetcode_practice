#include "shdstd.h"

int *spiralOrder(int **matrix, int size, int *col_size, int *ret_size)
{
	int rows = size;
	int cols = col_size[0];

	--rows;

	int lim = cols;

	int R = 0;
	int C = -1;

	*ret_size = size * (col_size[0]);
	int *result = malloc((*ret_size) * sizeof(int));
	int w = 0;

	int dr = 0;
	int dc = 1;

	for (;;) {
		if (lim <= 0) {
			break;
		}

		for (int i = 0; i < lim; ++i) {
			R += dr;
			C += dc;

			result[w++] = matrix[R][C];
		}

		if (dr != 0) {
			--rows;
			--cols;
			lim = cols;
		} else {
			lim = rows;
		}

		int tmp = dc;
		dc = -(dr);
		dr = tmp;
	}

	return result;
}
