#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
double champagneTower(int poured, int q_row, int q_col)
{
	if (poured < q_row + 1) {
		return 0;
	}

	double *layer = malloc((q_row + 2) * sizeof(double));
	layer[0] = (double)poured;

	for (int r = 0; r < q_row; ++r) {
		for (int c = r; c >= 0; --c) {
			double remained = MAX(layer[c] - 1.0, 0.0);
			layer[c] = remained * 0.5;
			layer[c+1] += remained * 0.5;
		}
	}

	double res = layer[q_col];

	free(layer);

	if (res <= 1.0) {
		return res;
	} else {
		return 1.0;
	}
}

/*
 *			1
 *		0.5		0.5
 *	0.25		0.5		0.25
 *0.125		0.375		0.375		0.125
 */
