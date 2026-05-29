#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int minElement(int *nums, int size)
{
	int best = INT32_MAX;

	for (int i = 0; i < size; ++i) {
		int num = nums[i];

		best = MIN(best, num);

		int new = 0;
		while (num) {
			new += num % 10;
			num /= 10;
		}
		best = MIN(best, new);
	}

	return best;
}
