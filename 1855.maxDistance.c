#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int maxDistance(int *left, int left_size, int *right, int right_size)
{
	int L = 0;

	int best = 0;

	for (int R = 0; R < right_size; ++R) {
		int right_num = right[R];

		while (L < left_size &&
			L < R &&
			left[L] > right_num) {
			++L;
		}
		if (L == left_size) {
			break;
		}

		best = MAX(best, R - L);
	}

	return best;
}
