#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int64_t maxMatrixSum(int **matrix, int size, int *col_size)
{
	int abs_min = INT32_MAX;

	int neg_count = 0;

	int64_t abs_sum = 0;

	for (int i = 0; i < size; ++i) {
		int lim = col_size[i];

		for (int i2 = 0; i2 < lim; ++i2) {
			int num = matrix[i][i2];
			int abs_num = abs(num);

			abs_min = MIN(abs_min, abs_num);
			abs_sum += abs_num;

			if (num < 0) {
				++neg_count;
			}
		}
	}

	if (neg_count % 2) {
		return abs_sum - (abs_min * 2);
	}

	return abs_sum;
}
