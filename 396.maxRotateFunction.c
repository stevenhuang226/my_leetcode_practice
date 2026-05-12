#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int maxRotateFunction(int *nums, int size)
{
	int64_t sum = 0;
	int64_t mult_sum = 0;
	for (int i = 0; i < size; ++i) {
		sum += nums[i];
		mult_sum += nums[i] * i;
	}

	int best = mult_sum;
	for (int i = size - 1; i >= 0; --i) {
		mult_sum += sum - (nums[i] * size);
		best = MAX(best, mult_sum);
	}

	return best;
}
