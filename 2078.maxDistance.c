#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int maxDistance(int *colors, int size)
{
	int most_left = colors[0];
	int most_right = colors[size-1];

	int best = 0;
	for (int L = 0; L < size; ++L) {
		if (colors[L] != most_right) {
			best = size - 1 - L;
			break;
		}
	}

	for (int R = size-1; R >= 0; --R) {
		if (colors[R] != most_left) {
			best = MAX(best, R);
			break;
		}
	}

	return best;
}
